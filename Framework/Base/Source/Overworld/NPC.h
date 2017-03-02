#ifndef NPC_H
#define NPC_H

#include <vector>
#include "OverworldEntity.h"

using std::vector;

class Mesh;

class NPC : public OverworldEntity
{
protected:
	enum NPC_STATES
	{
		IDLE,
		MOVE
	};

	vector<string> dialogue;
	vector<Vector3> waypoints;
	Vector3 view;
	string sfx;
	NPC_STATES state;
	int currentPoint;
	float idleTime;
	float idleDuration;
	float moveSpeed;
	Vector3 velocity;

	void HandleState();
	void Idle();
	void Move();

public:
	NPC();
	virtual ~NPC();

	virtual void Update();
	virtual void Interact();
	virtual void HandleCollision(EntityBase* entity);
	void LoadDialogue(string name);

	inline void SetMoveSpeed(float speed){ moveSpeed = speed; }
	void AddWaypoint(const Vector3& waypoint);

	inline void AttachSFX(string name) { sfx = name; }
};

#endif