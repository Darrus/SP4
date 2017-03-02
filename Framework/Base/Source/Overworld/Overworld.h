#ifndef OVERWORLD_H
#define OVERWORLD_H

#include <vector>

#include "OverworldBase.h"

#include "OverworldAsset.h"

#include "../Entity/SpriteEntity.h"
#include "../Entity/SkyBoxEntity.h"
#include "../Scenes/BattleState.h"
#include "../SpatialPartition/SpatialPartition.h"


using std::vector;

class Overworld : public OverworldBase
{
public:
	enum OVERWORLD_STATE
	{
		NAVIGATE,
		BATTLE
	};

	Overworld();
	virtual ~Overworld();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

	virtual void Pause();
	virtual void UnPause();
	
	static bool battle;

	bool tree;
private:
	SkyBoxEntity mountain;
    CBattleState* battlestate;
	float encounterRate;

	void HandleEncounter(float dt);
	void SpawnTrees(float radius, Vector3 center, int count);
	void SpawnTrees(Vector3 min, Vector3 max, int count);
};

#endif