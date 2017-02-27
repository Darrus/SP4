#pragma once
#include "OverworldBase.h"
class MountainTop : public OverworldBase
{
public:
	MountainTop();
	virtual ~MountainTop();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

	virtual void UnPause();
};

