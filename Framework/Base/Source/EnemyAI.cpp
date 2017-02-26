#include "EnemyAI.h"

EnemyAI::EnemyAI() :
aggroLvl(NEUTRAL),
iCrit(false),
iDodge(false)
{
    battlelog = new BattleLog();
}

EnemyAI::~EnemyAI()
{

}

void EnemyAI::DetermineAction(BattleEntity* entityAI, BattleEntity* player)
{
    entityAI->AddAttkTurnPt(1);

    switch (aggroLvl)
    {
    case HIGH:
        HighAggression(entityAI, player);
        break;
    case MODERATE:
        ModerateAggression(entityAI, player);
        break;
    case LOW:
        LowAggression(entityAI, player);
        break;
    case NEUTRAL:
        NeutralAggression(entityAI, player);
        break;
    default:
        break;
    }
}

void EnemyAI::HighAggression(BattleEntity* entityAI, BattleEntity* player)
{
    StatSystem AIStats = entityAI->GetInfo()->stats;
    StatSystem playerStats = player->GetInfo()->stats;

    if ((AIStats.GetRechargeRate() * 0.5) >= playerStats.GetRechargeRate())
    {
        if (entityAI->GetAttkTurnPt() < 2)
            Defend(entityAI);
        else
            AttackPlayer(entityAI, player);
    }
    if (CheckDamage(entityAI->GetDamage(), playerStats.GetDefence()) > 0)
    {
        while (entityAI->GetAttkTurnPt() > 0)
            AttackPlayer(entityAI, player);
    }
    else
    {
        //use skill
        AttackPlayer(entityAI, player);
        //Defend(entityAI);
    }
}
void EnemyAI::ModerateAggression(BattleEntity* entityAI, BattleEntity* player)
{
    StatSystem AIStats = entityAI->GetInfo()->stats;
    StatSystem playerStats = player->GetInfo()->stats;

    if ((AIStats.GetRechargeRate() * 0.5) >= playerStats.GetRechargeRate())
    {
        if (entityAI->GetAttkTurnPt() < 2)
            Defend(entityAI);
        else
            AttackPlayer(entityAI, player);
    }
    if (CheckDamage(entityAI->GetDamage(), playerStats.GetDefence()) > 0)
    {
        while (entityAI->GetAttkTurnPt() > 0)
            AttackPlayer(entityAI, player);
    }
    else
    {
        //use skill
        Defend(entityAI);
    }

}
void EnemyAI::LowAggression(BattleEntity* entityAI, BattleEntity* player)
{
    StatSystem AIStats = entityAI->GetInfo()->stats;
    StatSystem playerStats = player->GetInfo()->stats;

    if ((AIStats.GetRechargeRate() * 0.5) >= playerStats.GetRechargeRate())
    {
        if (entityAI->GetAttkTurnPt() < 2)
            Defend(entityAI);
        else
            AttackPlayer(entityAI, player);
    }
    if (CheckDamage(entityAI->GetDamage(), playerStats.GetDefence()) > 0)
    {
        while (entityAI->GetAttkTurnPt() > 0)
            AttackPlayer(entityAI, player);
    }
    else
    {
        //use skill
        Defend(entityAI);
    }
}
void EnemyAI::NeutralAggression(BattleEntity* entityAI, BattleEntity* player)
{
    StatSystem AIStats = entityAI->GetInfo()->stats;
    StatSystem playerStats = player->GetInfo()->stats;

    if (entityAI->GetHP() <= (AIStats.GetMaxHP() * 0.5))
    {
        if (entityAI->GetDefending() < 1.5)
            Defend(entityAI);
        else
        {
            if (CheckDamage(entityAI->GetDamage(), playerStats.GetDefence()) > 0)
            {
                while (entityAI->GetAttkTurnPt() > 0)
                    AttackPlayer(entityAI, player);
            }
        }
    }
    else
    {
        AttackPlayer(entityAI, player);
    }
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
            battlelog = new BattleLog(targetPlayer, myEntity->name, DamageDeal, DamageDeal, iDodge, iCrit);
            battlelog->battleloglist.push_back(battlelog);

            std::cout << "Dealt " << DamageDeal << " to " << targEntity->name << std::endl;
        }
        else
        {
            DamageDeal = 0;
            std::cout << targEntity->name << " has Dodged the Attack!" << std::endl;
        }

        if (targetPlayer->GetHP() <= 0)
        {
            targetPlayer->GetInfo()->HP = 0;
            std::cout << targEntity->name << " Eliminated!" << std::endl;
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
    entityAI->DecreaseAttkTurnPt(1);
}

void EnemyAI::CastSpell(BattleEntity* entityAI, BattleEntity* targetPlayer)
{
    entityAI->DecreaseAttkTurnPt(1);
}

void EnemyAI::Defend(BattleEntity* entityAI)
{
    entityAI->SetDefending(1.5);
    entityAI->AddAttkTurnPt(1);
    battlelog = new BattleLog(entityAI, true);
    battlelog->battleloglist.push_back(battlelog);
    ResetAIBar(entityAI);
}

void EnemyAI::ResetAIBar(BattleEntity* entityAI)
{
    std::cout << "Turn ended" << std::endl << std::endl;
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

int EnemyAI::CheckDamage(int dmg, int def)
{
    int DamageDeal = (dmg * 1.5) - def;

    return DamageDeal;
}