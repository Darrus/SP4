#pragma once
#include "OverworldBase.h"

class Town : public OverworldBase
{
private:
	SkyBoxEntity wall;

public:
	Town();
	virtual ~Town();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

	virtual void UnPause();
};

