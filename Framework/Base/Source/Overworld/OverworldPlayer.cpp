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


OverworldPlayer::OverworldPlayer() :
moveSpeed(25.f),
encounterRate(0.0f)
{
	view.Set(0.f, 1.f, 0.f);
	defaultView = view;
}


OverworldPlayer::~OverworldPlayer()
{
}

void OverworldPlayer::Update()
{
	position += velocity;
	velocity.SetZero();

	OverworldEntity::Update();
	Controls();
	HandleBoundary();

	camera->SetEntityPos(position);
	collider->SetOffset(velocity);
}

void OverworldPlayer::Controls()
{
	float dt = (float)StopWatch::GetInstance()->GetDeltaTime();
	Mtx44 mx;
	mx.SetToRotation(camera->GetRotZ(), 0.f, 0.f, 1.f);
	view = mx * defaultView;
	right = view.Cross(Vector3(0.f, 0.f, 1.f));

    if (KeyboardController::GetInstance()->IsKeyDown('W'))
    {
        velocity += view;
        HandleEncounter(dt);
    }
    else if (KeyboardController::GetInstance()->IsKeyDown('S'))
    {
        velocity -= view;
        HandleEncounter(dt);
    }
    if (KeyboardController::GetInstance()->IsKeyDown('D'))
    {
        velocity += right;
        HandleEncounter(dt);
    }
    else if (KeyboardController::GetInstance()->IsKeyDown('A'))
    {
        velocity -= right;
        HandleEncounter(dt);
    }

	if (velocity.LengthSquared() > 0)
		velocity = velocity.Normalized() * moveSpeed * dt;

	if (KeyboardController::GetInstance()->IsKeyPressed('E'))
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
}
void OverworldPlayer::HandleEncounter(float dt)
{
    encounterRate += dt;
    if (encounterRate > 5.f)
    {
        if (Math::RandFloatMinMax(10, 110) <= encounterRate)
        {
            Overworld::battle = true;
            camera->Transition(70.f, 0.f, 50.f);
            encounterRate = 0.f;
        }
    }
}

void OverworldPlayer::HandleCollision(EntityBase* entity)
{
	TriggerArea* trigger = dynamic_cast<TriggerArea*>(entity);
	if (trigger)
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
