#pragma once

#include "NPC.h"

class EnemyNPC : public NPC
{
public:
	EnemyNPC();
	virtual ~EnemyNPC();

	virtual void Update();
	virtual void Interact();
};

