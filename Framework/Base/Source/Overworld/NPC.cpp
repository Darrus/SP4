#include <fstream>
#include "NPC.h"

// Scenes
#include "SceneManager.h"
#include "../Scenes/DialogueScene.h"

// Utilities
#include "TriggerArea.h"
#include "Collider\Collider_2DAABB.h"
#include "timer.h"

NPC::NPC() :
currentPoint(0),
state(IDLE),
moveSpeed(1.f)
{
	idleDuration = 0.f;
	idleTime = idleDuration;
}


NPC::~NPC()
{
}

void NPC::LoadDialogue(string name)
{
	string fileName = "Dialogue//" + name + ".txt";
	std::ifstream file;
	file.open(fileName);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			dialogue.push_back(line);
		}
	}
	file.close();
}

void NPC::Update()
{
	OverworldEntity::Update();
	HandleState();
}

void NPC::Interact()
{
	DialogueScene* scene = dynamic_cast<DialogueScene*>(SceneManager::GetInstance()->SetActiveScene("Dialogue", true));
	if (scene)
	{
		scene->SetDialogue(dialogue);
	}
}

void NPC::HandleState()
{
	position += velocity;

	switch (state)
	{
	case IDLE:
		Idle();
		break;
	case MOVE:
		Move();
		break;
	}
}

void NPC::AddWaypoint(const Vector3& waypoint)
{
	this->waypoints.push_back(waypoint);
}

void NPC::Idle()
{
	float dt = (float)StopWatch::GetInstance()->GetDeltaTime();
	idleTime -= dt;
	if (idleTime < 0.f && waypoints.size() > 0)
	{
		idleTime = idleDuration;
		state = MOVE;
		Math::InitRNG();
		idleDuration = Math::RandFloatMinMax(1.f, 6.f);
	}
}

void NPC::Move()
{
	float dt = (float)StopWatch::GetInstance()->GetDeltaTime();
	Vector3 dist = waypoints[currentPoint] - position;
	float speed = moveSpeed * dt;

	if (dist.LengthSquared() < speed * speed)
	{
		state = IDLE;
		velocity.SetZero();
		currentPoint = (currentPoint + 1) % waypoints.size();
		return;
	}
	else
	{
		velocity = dist.Normalized() * moveSpeed * dt;
	}
}

void NPC::HandleCollision(EntityBase* entity)
{
	TriggerArea* trigger = dynamic_cast<TriggerArea*>(entity);
	if (trigger)
		return;

	state = IDLE;
	velocity.SetZero();
}