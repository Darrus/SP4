#ifndef ENEMYAI_H
#define ENEMYAI_H

#include "Entity\BattleEntity.h"
#include "BattleLog.h"

#include <list>

class EnemyAI : public BattleEntity
{
private:
    bool iCrit, iDodge;

public:
    EnemyAI();
    ~EnemyAI();

    enum AGGRESSIONLVL
    {
        NEUTRAL = 0,
        LOW,
        MODERATE,
        HIGH,
    };

    AGGRESSIONLVL aggroLvl;

    void DetermineAction(BattleEntity* entityAI, BattleEntity* player);
    void AttackPlayer(BattleEntity* entityAI, BattleEntity* targetPlayer);
    void CastSpell(BattleEntity* entityAI);
    void CastSpell(BattleEntity* entityAI, BattleEntity* targetPlayer);
    void Defend(BattleEntity* entityAI);

    void ResetAIBar(BattleEntity* entityAI);
    void CheckCrit(float crit);
    void CheckDodge(float dodge);
    int CheckDamage(int dmg, int def);

    ///< BattleLog
    BattleLog* battlelog;
};

#endif /* ENEMYAI_H */