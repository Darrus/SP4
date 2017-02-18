#include "Entity\BattleEntity.h"

#ifndef ENEMYAI_H
#define ENEMYAI_H

class EnemyAI : public BattleEntity
{
private:
    bool iCrit, iDodge;

public:
    EnemyAI();
    ~EnemyAI();

    void DetermineAction(BattleEntity* entityAI, BattleEntity* player);
    void AttackPlayer(BattleEntity* entityAI, BattleEntity* targetPlayer);
    void CastSpell(BattleEntity* entityAI);
    void CastSpell(BattleEntity* entityAI, BattleEntity* targetPlayer);
    void Defend(BattleEntity* entityAI);

    void ResetAIBar(BattleEntity* entityAI);
    void CheckCrit(float crit);
    void CheckDodge(float dodge);
};

#endif /* ENEMYAI_H */