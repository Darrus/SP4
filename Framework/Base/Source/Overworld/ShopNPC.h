#pragma once

#include "NPC.h"

class ShopNPC : public NPC
{
private:
	string targetScene;

public:
	ShopNPC();
	virtual ~ShopNPC();

	virtual void Interact();

	inline void SetTargetScene(const string& scene){ targetScene = scene; }
};

