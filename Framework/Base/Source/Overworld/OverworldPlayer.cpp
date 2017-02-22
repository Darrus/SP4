#include "OverworldPlayer.h"

// Interactable
#include "NPC.h"

// Collider
#include "Collider\Collider_2DAABB.h"

// Utilities
#include "timer.h"
#include "KeyboardController.h"
#include "SceneManager.h"
#include "Overworld.h"


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
	position += velocity;
	velocity.SetZero();

	OverworldEntity::Update();
	Controls();

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
		velocity += view;
	else if (KeyboardController::GetInstance()->IsKeyDown('S'))
		velocity -= view;
	if (KeyboardController::GetInstance()->IsKeyDown('D'))
		velocity += right;
	else if (KeyboardController::GetInstance()->IsKeyDown('A'))
		velocity -= right;

	if (velocity.LengthSquared() > 0)
		velocity = velocity.Normalized() * moveSpeed * dt;

	if (KeyboardController::GetInstance()->IsKeyPressed('E'))
	{
		Overworld* scene = dynamic_cast<Overworld*>(SceneManager::GetInstance()->GetActiveScene());
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
							npc->HandleCollision(nullptr);
					}
				}
			}
		}
	}
}

void OverworldPlayer::HandleCollision(EntityBase* entity)
{
	CCollider_2DAABB check;
	check.SetScale(collider->GetScale());

	check.SetOffset(Vector3(position.x + velocity.x, position.y, position.z));

	if (check.CheckCollision(entity->GetCollider()))
		velocity.x = 0.f;

	check.SetOffset(Vector3(position.x, position.y + velocity.y, position.z));
	if (check.CheckCollision(entity->GetCollider()))
		velocity.y = 0.f;
}