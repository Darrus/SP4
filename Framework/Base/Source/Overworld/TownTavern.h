#pragma once
#include "OverworldBase.h"

class TownTavern : public OverworldBase
{
public:
	TownTavern();
	virtual ~TownTavern();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

	virtual void UnPause();
};

