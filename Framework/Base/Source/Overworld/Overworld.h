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
	virtual void UnPause();
	
	static bool battle;
private:
	SkyBoxEntity mountain;
    CBattleState* battlestate;
	float encounterRate;

	void HandleEncounter(float dt);
};

#endif