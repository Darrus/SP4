#ifndef BATTLE_ENTITY_H
#define BATTLE_ENTITY_H

#include "Entity2D.h"
#include "../Character/InfoBase.h"

class BattleEntity : public Entity2D 
{
	InfoBase* info;
	const float maxATB;
	float ATB;

	bool isDead;
	bool isReady;

public:
	BattleEntity();
	virtual ~BattleEntity();

	virtual void Update();

	int GetDamage();
	int GetHP();
	void TakeDamage(int damage);
};

#endif