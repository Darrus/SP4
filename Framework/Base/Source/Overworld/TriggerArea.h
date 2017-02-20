#pragma once

#include <string>

#include "EntityBase.h"
#include "CameraFollow.h"

using std::string;

class TriggerArea : public EntityBase
{
	string targetScene;
	CameraFollow* camera;
	bool trigger;

public:
	TriggerArea();
	~TriggerArea();

	virtual void Update();
	virtual void HandleCollision(EntityBase* entity);

	inline void SetScene(string scene){ this->targetScene = scene; }
	inline void SetCamera(CameraFollow* camera) { this->camera = camera; }
};

