#pragma once
#include "../Entity/AssetEntity.h"
#include "CameraFollow.h"

class OverworldAsset : public AssetEntity
{
	float rotX;
	float rotZ;
	CameraFollow* camera;

public:
	OverworldAsset(const string& meshName);
	virtual ~OverworldAsset();

	virtual void Update();
	virtual void Render();
	virtual void HandleCollision(EntityBase* entity);

	inline void SetCamera(CameraFollow* camera){ this->camera = camera; }
};

