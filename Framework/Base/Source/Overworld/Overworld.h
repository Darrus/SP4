#ifndef OVERWORLD_H
#define OVERWORLD_H

#include "Scene.h"
#include <vector>

#include "CameraFollow.h"
#include "OverworldPlayer.h"
#include "OverworldAsset.h"
#include "NPC.h"

#include "../Entity/SpriteEntity.h"
#include "../Entity/SkyBoxEntity.h"
#include "../Scenes/BattleState.h"
#include "../SpatialPartition/SpatialPartition.h"


using std::vector;

class Overworld : public Scene
{
public:
	Overworld();
	virtual ~Overworld();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

	virtual void UnPause();
	
	static bool battle;

	inline CSpatialPartition* GetSpatialPartition() { return &spatial; }

private:
	CameraFollow camera;
	SpriteEntity* background;
	SkyBoxEntity* skybox;

    CBattleState* battlestate;
	
	CSpatialPartition spatial;

	OverworldPlayer* player;
	NPC* npc;
};

#endif