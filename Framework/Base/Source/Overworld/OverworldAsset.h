#pragma once
#include "../Entity/AssetEntity.h"
#include "../Camera.h"

class OverworldAsset : public AssetEntity
{
	float rotX;
	float rotY;
	bool battle;
	Camera* camera;

public:
	OverworldAsset(const string& meshName);
	virtual ~OverworldAsset();

	virtual void Update();
	virtual void Render();

	inline void SetCamera(Camera* camera){ this->camera = camera; }
};

