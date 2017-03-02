#include <fstream>
#include "NPC.h"

// Scenes
#include "SceneManager.h"
#include "../Scenes/DialogueScene.h"

// Utilities
#include "TriggerArea.h"
#include "Collider\Collider_2DAABB.h"
#include "timer.h"
#include "SoundEngine\SoundEngine.h"

NPC::NPC() :
currentPoint(0),
state(IDLE),
moveSpeed(1.f)
{
	idleDuration = 0.f;
	idleTime = idleDuration;
	view.Set(0.f, 1.f, 0.f);
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
		SoundEngine::GetInstance()->Play(sfx);
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
	Vector3 dir = (camera->GetCameraPos() - position).Normalized();
	float angle = Math::RadianToDegree(acos(dir.Dot(view)));
	Vector3 test = view.Cross(dir);
	if (test.z < 0)
		angle = -angle;

	if (angle < 45 && angle > -45)
		anim.PlayAnimation("npc_idle_front");
	else if (angle > 135 || angle < -135)
		anim.PlayAnimation("npc_idle_back");
	else if (angle < 0 && angle > -135)
		anim.PlayAnimation("npc_idle_right");
	else if (angle > 0 && angle < 135)
		anim.PlayAnimation("npc_idle_left");

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
		view = dist.Normalized();
		velocity.SetZero();
		currentPoint = (currentPoint + 1) % waypoints.size();
		return;
	}
	else
	{
		velocity = dist.Normalized() * moveSpeed * dt;
	}

	Vector3 dir = (camera->GetCameraPos() - position).Normalized();
	view = velocity.Normalized();
	float angle = Math::RadianToDegree(acos(dir.Dot(view)));
	Vector3 test = view.Cross(dir);
	if (test.z < 0)
		angle = -angle;

	if (angle < 45 && angle > -45)
		anim.PlayAnimation("npc_walk_front");
	else if (angle > 135 || angle < -135)
		anim.PlayAnimation("npc_walk_back");
	else if (angle < 0 && angle > -135)
		anim.PlayAnimation("npc_walk_right");
	else if (angle > 0 && angle < 135)
		anim.PlayAnimation("npc_walk_left");
}

void NPC::HandleCollision(EntityBase* entity)
{
	TriggerArea* trigger = dynamic_cast<TriggerArea*>(entity);
	if (trigger)
		return;

	state = IDLE;
	velocity.SetZero();
}