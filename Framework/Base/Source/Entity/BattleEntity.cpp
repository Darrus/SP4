#include "BattleEntity.h"
#include "timer.h"

BattleEntity::BattleEntity() :
maxATB(100.f),
ATB(0.f), 
isReady(false),
isDead(false),
defendRatio(1),
AttkTurnPt(0),
enemyType(ENEMY)
{
    // Temporary
    info = new InfoBase();
}


BattleEntity::~BattleEntity()
{
}

void BattleEntity::Update()
{
	if (info)
	{
		info->Update();
		if (info->HP <= 0.f)
		{
			isDead = true;
			return;
		}
	}
	

	float dt = (double)StopWatch::GetInstance()->GetDeltaTime();

	if (ATB < maxATB)
		ATB += info->stats.GetRechargeRate() * dt;
	else
		isReady = true;
}

int BattleEntity::GetDamage()
{
	return info->stats.GetDamage();
}

int BattleEntity::GetHP()
{
	return info->HP;
}

void BattleEntity::TakeDamage(int damage)
{
	info->HP -= damage;
}
