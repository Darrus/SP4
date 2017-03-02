#include "OverworldPlayer.h"

// Interactable
#include "NPC.h"
#include "TriggerArea.h"

// Collider
#include "Collider\Collider_2DAABB.h"

// Utilities
#include "timer.h"
#include "KeyboardController.h"
#include "SceneManager.h"
#include "OverworldBase.h"
#include "Overworld.h"
#include "../Player/Player.h"

OverworldPlayer::OverworldPlayer() :
moveSpeed(25.f)
{
	view.Set(0.f, 1.f, 0.f);
	defaultView = view;
}


OverworldPlayer::~OverworldPlayer()
{
}

void OverworldPlayer::Update()
{
	OverworldEntity::Update();
	HandleBoundary();
	position += velocity;
	velocity.SetZero();

	camera->SetEntityPos(position);
}

bool OverworldPlayer::Controls()
{
	CharacterInfo* leader = Player::GetInstance().GetParty()->GetLeader();
	if (leader->name != leaderName)
	{
		anim.CopyAnimator(leader->anim);
		leaderName = leader->name;
	}

	bool moving = false;
	float dt = (float)StopWatch::GetInstance()->GetDeltaTime();
	Mtx44 mx;
	mx.SetToRotation(camera->GetRotZ(), 0.f, 0.f, 1.f);
	view = mx * defaultView;
	right = view.Cross(Vector3(0.f, 0.f, 1.f));

    if (KeyboardController::GetInstance()->IsKeyDown('W'))
    {
        velocity += view;
		moving = true;
		if(!KeyboardController::GetInstance()->IsKeyDown('D') &&
			!KeyboardController::GetInstance()->IsKeyDown('A'))
			anim.PlayAnimation(leaderName + "_walk_back");
    }
    else if (KeyboardController::GetInstance()->IsKeyDown('S'))
    {
        velocity -= view;
		moving = true;
		if (!KeyboardController::GetInstance()->IsKeyDown('D') &&
			!KeyboardController::GetInstance()->IsKeyDown('A'))
			anim.PlayAnimation(leaderName + "_walk_front");
    }
    if (KeyboardController::GetInstance()->IsKeyDown('D'))
    {
        velocity += right;
		moving = true;
		anim.PlayAnimation(leaderName + "_walk_right");
    }
    else if (KeyboardController::GetInstance()->IsKeyDown('A'))
    {
        velocity -= right;
		moving = true;
		anim.PlayAnimation(leaderName + "_walk_left");
    }

	if (velocity.LengthSquared() > 0)
	{
		velocity = velocity.Normalized() * moveSpeed * dt;
	}



	if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
	{
		OverworldBase* scene = dynamic_cast<OverworldBase*>(SceneManager::GetInstance()->GetActiveScene());
		if (scene)
		{
			CSpatialPartition* spatial = scene->GetSpatialPartition();
			CCollider_2DAABB interact;
			Vector3 interactPos = position + view * scale.x;
			interact.SetOffset(Vector3(interactPos.x, interactPos.y, interactPos.z));
			interact.SetScale(scale);
			CGrid* grid = spatial->GetGrid(interactPos);
			if (grid)
			{
				std::vector<EntityBase*>* objects = grid->GetListOfObject();
				for (int i = 0; i < objects->size(); ++i)
				{
					if (interact.CheckCollision((*objects)[i]->GetCollider()))
					{
						NPC* npc = dynamic_cast<NPC*>((*objects)[i]);
						if (npc)
							npc->Interact();
					}
				}
			}
		}
	}
	if (!moving)
		anim.PlayAnimation(leaderName + "_idle_front");
	
	collider->SetOffset(velocity);
	return moving;
}

void OverworldPlayer::HandleCollision(EntityBase* entity)
{
	TriggerArea* trigger = dynamic_cast<TriggerArea*>(entity);
	if (trigger)
		return;

	if (entity == ground)
		return;

	CCollider_2DAABB check;
	check.SetScale(collider->GetScale());

	check.SetOffset(Vector3(position.x + velocity.x, position.y, position.z));

	if (check.CheckCollision(entity->GetCollider()))
		velocity.x = 0.f;

	check.SetOffset(Vector3(position.x, position.y + velocity.y, position.z));
	if (check.CheckCollision(entity->GetCollider()))
		velocity.y = 0.f;
}

void OverworldPlayer::HandleBoundary()
{
	Vector3 newPos = position + velocity;
	Vector3 boundary = ground->GetScale() * 0.5f;
	if (newPos.x + scale.x * 0.5f > boundary.x || newPos.x - scale.x * 0.5f < -boundary.x)
		velocity.x = 0.f;
	if (newPos.y + scale.y * 0.5f > boundary.y || newPos.y - scale.y * 0.5f < -boundary.y)
		velocity.y = 0.f;
}

void OverworldPlayer::HandleAnim()
{
	if (velocity.LengthSquared() > 0)
	{
		Vector3 dir = (camera->GetCameraPos() - position).Normalized();
		view = velocity.Normalized();
		float angle = Math::RadianToDegree(acos(dir.Dot(view)));
		Vector3 test = view.Cross(dir);
		if (test.z < 0)
			angle = -angle;

		if (angle < 45 && angle > -45)
			anim.PlayAnimation(leaderName + "_walk_front");
		else if (angle > 135 || angle < -135)
			anim.PlayAnimation(leaderName + "_walk_back");
		else if (angle < 0 && angle > -135)
			anim.PlayAnimation(leaderName + "_walk_right");
		else if (angle > 0 && angle < 135)
			anim.PlayAnimation(leaderName + "_walk_left");
	}
	else
	{
		Vector3 dir = (camera->GetCameraPos() - position).Normalized();
		float angle = Math::RadianToDegree(acos(dir.Dot(view)));
		Vector3 test = view.Cross(dir);
		if (test.z < 0)
			angle = -angle;

		if (angle < 45 && angle > -45)
			anim.PlayAnimation(leaderName + "_idle_front");
		else if (angle > 135 || angle < -135)
			anim.PlayAnimation(leaderName + "_idle_back");
		else if (angle < 0 && angle > -135)
			anim.PlayAnimation(leaderName + "_idle_right");
		else if (angle > 0 && angle < 135)
			anim.PlayAnimation(leaderName + "_idle_left");
	}
}