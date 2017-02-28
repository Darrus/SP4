#pragma once

#include "NPC.h"

class ShopNPC : public NPC
{
public:
	ShopNPC();
	virtual ~ShopNPC();

	virtual void Update();
	virtual void Interact();
};

