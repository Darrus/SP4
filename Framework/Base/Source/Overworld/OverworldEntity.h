#ifndef OVERWORLD_ENTITY_H
#define OVERWORLD_ENTITY_H

#include "../Entity/Entity2D.h"
#include "CameraFollow.h"

class OverworldEntity : public Entity2D
{
	float moveSpeed;
	CameraFollow* camera;
	Vector3 front, right;
	Vector3 velocity;

public:
	OverworldEntity();
	~OverworldEntity();

	virtual void Update();
	virtual void HandleCollision(EntityBase* entity);

	inline void AttachCamera(CameraFollow* camera) { this->camera = camera; }
	inline void DeattachCamera() { this->camera = nullptr; }
};

#endif