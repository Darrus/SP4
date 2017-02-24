#pragma once
#include "../Entity/AssetEntity.h"
#include "CameraFollow.h"

class OverworldAsset : public AssetEntity
{
protected:
	CameraFollow* camera;

public:
	OverworldAsset(const string& meshName);
	virtual ~OverworldAsset();

	virtual void Render();

	inline void SetCamera(CameraFollow* camera){ this->camera = camera; }
};

