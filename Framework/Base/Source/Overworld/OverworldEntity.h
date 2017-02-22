#ifndef OVERWORLD_ENTITY_H
#define OVERWORLD_ENTITY_H

#include "../Entity/Entity2D.h"
#include "CameraFollow.h"

class OverworldEntity : public Entity2D
{
protected:
	CameraFollow* camera;

public:
	OverworldEntity();
	~OverworldEntity();

	virtual void Update();
	virtual void Render();

	inline void AttachCamera(CameraFollow* camera) { this->camera = camera; }
	inline void DeattachCamera() { this->camera = nullptr; }
};

#endif