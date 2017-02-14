#include "BattleEntity.h"
#include "timer.h"

BattleEntity::BattleEntity() :
info(nullptr), maxATB(100.f), ATB(0.f)
{
}


BattleEntity::~BattleEntity()
{
}

void BattleEntity::Update()
{
	float dt = (double)StopWatch::GetInstance()->GetDeltaTime();
	if (ATB < maxATB)
		ATB += info->stats.GetRechargeRate() * dt;
	else
	{
		isReady = true;
	}
	
}

void BattleEntity::Render()
{

}

void BattleEntity::RenderUI()
{

}
