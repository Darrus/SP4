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
    int partySize = Player::GetInstance().GetParty()->memberCount();
    
    if (partySize <= 1)
        aggroLvl = HIGH;
    if (partySize <= 2)
        aggroLvl = MODERATE;
    if (partySize <= 3)
        aggroLvl = LOW;
    else
        aggroLvl = NEUTRAL;

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
        if (playerStats.GetDodgeRate() >= 50 || playerStats.GetCritRate() >= 50)
        {
            if (entityAI->GetAttkTurnPt() < 4)
                Defend(entityAI);
            else
            {
                while (entityAI->GetAttkTurnPt() > 0)
                    AttackPlayer(entityAI, player);
            }
        }
        else
                AttackPlayer(entityAI, player);
    }
    else if (entityAI->GetHP() <= AIStats.GetMaxHP() * 0.75)
    {
        if (entityAI->GetAttkTurnPt() < 2)
            Defend(entityAI);
        else
            while (entityAI->GetAttkTurnPt() > 0)
                AttackPlayer(entityAI, player);
    }
    else if (player->GetHP() <= playerStats.GetMaxHP() * 0.5)
    {
        while (entityAI->GetAttkTurnPt() > 0)
            AttackPlayer(entityAI, player);
    }
    else
    {
        //use skill
        while (entityAI->GetAttkTurnPt() > 0)
            AttackPlayer(entityAI, player);
        //Defend(entityAI);
    }
}
void EnemyAI::ModerateAggression(BattleEntity* entityAI, BattleEntity* player)
{
    StatSystem AIStats = entityAI->GetInfo()->stats;
    StatSystem playerStats = player->GetInfo()->stats;

    if ((AIStats.GetDamage()) >= playerStats.GetDamage())
    {
        if (entityAI->GetAttkTurnPt() < 2)
            Defend(entityAI);
        else
        {
            while (entityAI->GetAttkTurnPt() > 0)
                AttackPlayer(entityAI, player);
        }
    }
    else if (entityAI->GetInfo()->HP > player->GetInfo()->HP)
        AttackPlayer(entityAI, player);
    else
    {
        if (entityAI->GetAttkTurnPt() < 3)
            Defend(entityAI);
        else
        {
            while (entityAI->GetAttkTurnPt() > 0)
                AttackPlayer(entityAI, player);
        }
    }
}
void EnemyAI::LowAggression(BattleEntity* entityAI, BattleEntity* player)
{
    StatSystem AIStats = entityAI->GetInfo()->stats;
    StatSystem playerStats = player->GetInfo()->stats;

    if (entityAI->GetHP() <= (AIStats.GetMaxHP() * 0.5))
    {
        if (entityAI->GetAttkTurnPt() >= 2)
        {
            while (entityAI->GetAttkTurnPt() > 0)
                AttackPlayer(entityAI, player);
        }
        else
            Defend(entityAI);
    }
    else
    {
        if (CheckDamage(entityAI->GetDamage(), playerStats.GetDefence()) > 0)
        {
            while (entityAI->GetAttkTurnPt() > 0)
                AttackPlayer(entityAI, player);
        }
        else
            Defend(entityAI);
    }
}
void EnemyAI::NeutralAggression(BattleEntity* entityAI, BattleEntity* player)
{
    StatSystem AIStats = entityAI->GetInfo()->stats;
    StatSystem playerStats = player->GetInfo()->stats;

    if (entityAI->GetHP() <= (AIStats.GetMaxHP() * 0.5) && entityAI->GetAttkTurnPt() < 3)
        Defend(entityAI);
    else
        while (entityAI->GetAttkTurnPt() > 0)
            AttackPlayer(entityAI, player);
}

void EnemyAI::AttackPlayer(BattleEntity* entityAI, BattleEntity* targetPlayer)
{
    InfoBase* myEntity = entityAI->GetInfo();
    InfoBase* targEntity = targetPlayer->GetInfo();

    myEntity->stats.GetCritRate();

    if (targetPlayer != nullptr)
    {
        int DamageDeal;
        CheckCrit(myEntity->stats.GetCritRate());
        CheckDodge(targEntity->stats.GetDodgeRate());
        if (!iDodge)
        {
            if (iCrit)
            {
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
        }
        else
        {
            DamageDeal = 3;
            battlelog = new BattleLog(targetPlayer, myEntity->name, DamageDeal, DamageDeal, iDodge, iCrit);
            battlelog->battleloglist.push_back(battlelog);
        }

        if (targetPlayer->GetHP() <= 0)
            targetPlayer->GetInfo()->HP = 0;

        entityAI->SetDefending(1);
        entityAI->DecreaseAttkTurnPt(1);

        if (entityAI->GetAttkTurnPt() <= 0)
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
    entityAI->SetATB(0.0);
    entityAI->GetInfo()->stats.UpdateStats();
    entityAI->SetReady(false);
}

void EnemyAI::CheckCrit(float crit)
{
    int critcrit = 0;
    if (crit >= 80)
        critcrit = 80;
    else
        critcrit = crit;

    if (critcrit >= (Math::RandFloatMinMax(0, 100)))
        iCrit = true;
    else
        iCrit = false;
}

void EnemyAI::CheckDodge(float dodge)
{
    int dodgedodge = 0;
    if (dodge >= 80)
        dodgedodge = 80;
    else
        dodgedodge = dodge;

    if (dodgedodge >= (Math::RandFloatMinMax(0, 100)))
        iDodge = true;
    else
        iDodge = false;
}

int EnemyAI::CheckDamage(int dmg, int def)
{
    int DamageDeal = (dmg * 1.5) - def;

    return DamageDeal;
}