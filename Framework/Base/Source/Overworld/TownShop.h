#pragma once
#include "OverworldBase.h"
class TownShop :
	public OverworldBase
{
private:
	NPC* npc;

public:
	TownShop();
	virtual ~TownShop();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

