#ifndef BATTLE_ENTITY_H
#define BATTLE_ENTITY_H

#include "Entity2D.h"
#include "../Character/CharacterInfo.h"

class BattleEntity : public Entity2D 
{
	CharacterInfo* info;
	const float maxATB;
	float ATB;

	bool isDead;
	bool isReady;

public:
	BattleEntity();
	virtual ~BattleEntity();

	virtual void Update();
	virtual void Render();
	virtual void RenderUI();
};

#endif