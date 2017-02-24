#pragma once

#include "Scene.h"

// Utilities
#include "CameraFollow.h"
#include "../SpatialPartition/SpatialPartition.h"


// Entities
#include "OverworldPlayer.h"
#include "NPC.h"
#include "../Entity/SpriteEntity.h"
#include "../Entity/SkyBoxEntity.h"

class OverworldBase : public Scene
{
public:
	OverworldBase();
	virtual ~OverworldBase();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

	inline CSpatialPartition* GetSpatialPartition() { return &spatial; }

protected:
	CameraFollow camera;
	CSpatialPartition spatial;
	OverworldPlayer player;
	SkyBoxEntity skybox;
	SpriteEntity background;
};

