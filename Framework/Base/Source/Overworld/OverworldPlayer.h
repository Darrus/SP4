#pragma once

#include "OverworldEntity.h"
#include "../Entity/SpriteEntity.h"

class OverworldPlayer :	public OverworldEntity
{
	Vector3 defaultView;
	Vector3 view, right;
	Vector3 velocity;
	SpriteEntity* ground;
	float moveSpeed;
	
	void Controls();
	void HandleBoundary();

public:
	OverworldPlayer();
	virtual ~OverworldPlayer();

	virtual void Update();
	virtual void HandleCollision(EntityBase* entity);

	inline void SetGround(SpriteEntity* ground){ this->ground = ground; }
};

