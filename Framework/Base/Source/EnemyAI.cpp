#include "EnemyAI.h"

EnemyAI::EnemyAI()
{

}

EnemyAI::~EnemyAI()
{

}

void EnemyAI::DetermineAction(BattleEntity* entityAI, BattleEntity* player)
{
    AttackPlayer(entityAI, player);
}

void EnemyAI::AttackPlayer(BattleEntity* entityAI, BattleEntity* targetPlayer)
{
    InfoBase* myEntity = entityAI->GetInfo();
    InfoBase* targEntity = targetPlayer->GetInfo();

    myEntity->stats.GetCritRate();

    if (targetPlayer != nullptr)
    {
        std::cout << targEntity->name << "'s Health: " << targetPlayer->GetHP() << std::endl;
        std::cout << myEntity->name << "'s Health : " << entityAI->GetHP() << std::endl;

        int DamageDeal;
        CheckCrit(myEntity->stats.GetCritRate());
        CheckDodge(targEntity->stats.GetDodgeRate());
        if (!iDodge)
        {
            if (iCrit)
            {
                std::cout << myEntity->name << " has Crited!" << std::endl;
                DamageDeal = (myEntity->stats.GetDamage() * 1.5) - (targEntity->stats.GetDefence() * targetPlayer->GetDefending());
                if (DamageDeal <= 0)
                    DamageDeal = 0;
            }
            else
            {
                DamageDeal = myEntity->stats.GetDamage() - (targEntity->stats.GetDefence() * targetPlayer->GetDefending());
                if (DamageDeal <= 0)
                    DamageDeal = 0;
            }
            targetPlayer->TakeDamage(DamageDeal);

            std::cout << "Dealt " << DamageDeal << " to " << targEntity->name << std::endl;
        }
        else
        {
            DamageDeal = 0;
            std::cout << targEntity->name << " has Dodged the Attack!" << std::endl;
        }

        if (targetPlayer->GetHP() <= 0)
        {
            std::cout << targEntity->name << " Elimited!" << std::endl;
        }

        entityAI->SetDefending(1);
        entityAI->DecreaseAttkTurnPt(1);

        if (entityAI->GetAttkTurnPt() > 0)
            std::cout << "You gain another turn!" << std::endl << std::endl;
        else
            ResetAIBar(entityAI);
    }
}

void EnemyAI::CastSpell(BattleEntity* entityAI)
{

}

void EnemyAI::CastSpell(BattleEntity* entityAI, BattleEntity* targetPlayer)
{

}

void EnemyAI::Defend(BattleEntity* entityAI)
{
    entityAI->SetDefending(1.5);
    ResetAIBar(entityAI);
}

void EnemyAI::ResetAIBar(BattleEntity* entityAI)
{
    entityAI->SetATB(0.0);
    entityAI->SetReady(false);
}

void EnemyAI::CheckCrit(float crit)
{
    if (crit >= (Math::RandFloatMinMax(0, 100)))
        iCrit = true;
    else
        iCrit = false;
}

void EnemyAI::CheckDodge(float dodge)
{
    if (dodge >= (Math::RandFloatMinMax(0, 100)))
        iDodge = true;
    else
        iDodge = false;
}