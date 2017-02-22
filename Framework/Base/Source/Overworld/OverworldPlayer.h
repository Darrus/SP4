#pragma once
#include "OverworldEntity.h"

class OverworldPlayer :	public OverworldEntity
{
	Vector3 defaultView;
	Vector3 view, right;
	Vector3 velocity;
	float moveSpeed;

	void Controls();

public:
	OverworldPlayer();
	virtual ~OverworldPlayer();

	virtual void Update();
	virtual void HandleCollision(EntityBase* entity);
};

