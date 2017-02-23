#pragma once

#include <string>

#include "EntityBase.h"
#include "CameraFollow.h"

using std::string;

class TriggerArea : public EntityBase
{
protected:
	bool trigger;
	bool active;

	virtual void OnTrigger();

public:
	TriggerArea();
	~TriggerArea();

	virtual void HandleCollision(EntityBase* entity);
};

