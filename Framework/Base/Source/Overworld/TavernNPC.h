#pragma once

#include "NPC.h"

class TavernNPC : public NPC
{
private:
	string targetScene;

public:
	TavernNPC();
	virtual ~TavernNPC();

	virtual void Interact();

	inline void SetTargetScene(const string& scene){ targetScene = scene; }
};

