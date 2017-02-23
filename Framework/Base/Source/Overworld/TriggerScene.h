#pragma once

#include "TriggerArea.h"

class TriggerScene : public TriggerArea
{
	string targetScene;
	CameraFollow* camera;

	virtual void OnTrigger();

public:
	TriggerScene();
	virtual ~TriggerScene();

	virtual void Update();

	inline void SetScene(string scene){ this->targetScene = scene; }
	inline void SetCamera(CameraFollow* camera) { this->camera = camera; }
};

