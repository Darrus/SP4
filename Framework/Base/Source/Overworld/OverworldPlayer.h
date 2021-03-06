#pragma once

#include "OverworldEntity.h"
#include "../Entity/SpriteEntity.h"

class OverworldPlayer :	public OverworldEntity
{
	Vector3 defaultView;
	Vector3 view, right;
	Vector3 velocity;
	SpriteEntity* ground;
	string leaderName;
	float moveSpeed;
	
	void HandleBoundary();
	void HandleAnim();

public:
	OverworldPlayer();
	virtual ~OverworldPlayer();

	bool Controls();

	virtual void Update();
	virtual void HandleCollision(EntityBase* entity);

	inline void SetGround(SpriteEntity* ground){ this->ground = ground; }
	inline void SetLeaderName(string name) { this->leaderName = name; }
};

