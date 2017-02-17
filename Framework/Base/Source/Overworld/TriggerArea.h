#pragma once

#include <string>

#include "EntityBase.h"
#include "CameraFollow.h"

using std::string;

class TriggerArea : public EntityBase
{
	string targetScene;

public:
	TriggerArea();
	~TriggerArea();

	virtual void HandleCollision(EntityBase* entity);
};

