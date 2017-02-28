#pragma once
#include "OverworldBase.h"

class Cave : public OverworldBase
{
public:
	Cave();
	virtual ~Cave();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

	virtual void UnPause();
};

