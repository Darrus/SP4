#include "BattleSystem.h"


BattleSystem::BattleSystem() : 
anEntityTurn(false)
{
}


BattleSystem::~BattleSystem()
{
}

void BattleSystem::Update()
{
    // Loops through the Entire Battle entities to call their Updates;
    for (std::list<BattleEntity*>::iterator itr = BattleList.begin(); itr != BattleList.end(); itr++)
    {
        // Update Every Entity First to fill up their Attack Turn Bar
        if (!anEntityTurn)
            (*itr)->Update();

        // Check if any entity is ready, if it is, stop the update of others.
        if ((*itr)->GetReady())
        {
            anEntityTurn = true;
            EntityTurn((*itr));
        }
    }
}

// This Entity can do whatever it's turn is.
void BattleSystem::EntityTurn(BattleEntity* entity)
{
    //CharacterInfo* theEntityInfo = entity->GetChara();
    

    //theEntityInfo->
}

void BattleSystem::Attack(BattleEntity* entity, BattleEntity* targetEntity)
{
    //CharacterInfo* myEntity = entity->GetChara();
    //CharacterInfo* targEntity = targetEntity->GetChara();
    //
    //targEntity->HP -  myEntity->stats.GetDamage();
}

void BattleSystem::Render()
{
    for (std::list<BattleEntity*>::iterator itr = BattleList.begin(); itr != BattleList.end(); itr++)
    {
        if (!(*itr)->GetDead())
            (*itr)->Render();
    }
}