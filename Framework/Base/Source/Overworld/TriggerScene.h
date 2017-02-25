#pragma once

#include "TriggerArea.h"

class TriggerScene : public TriggerArea
{
	string targetScene;
	CameraFollow* camera;
	Vector3 startPos;

	virtual void OnTrigger();

public:
	TriggerScene();
	virtual ~TriggerScene();

	void Init(const string& scene, CameraFollow* camera, const Vector3& playerStartPos);
	void Init(const string& scene, CameraFollow* camera);
	virtual void Update();

	inline void SetScene(const string& scene){ this->targetScene = scene; }
	inline void SetCamera(CameraFollow* camera) { this->camera = camera; }
	inline void SetStartPosition(const Vector3& playerStartPos){ startPos = playerStartPos; }
};

