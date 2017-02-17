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
	virtual void Render();

	inline void AttachCamera(CameraFollow* camera) { 
		this->camera = camera;
		this->camera->SetCameraPos(position + Vector3(0.f, 0.f, 1.f));
		this->camera->SetCameraTarget(position);
	}
	inline void DeattachCamera() { this->camera = nullptr; }
};

#endif