#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include <list>

#include "..\Character\CharacterInfo.h"
#include "..\Party\PartySystem.h"
#include "..\Entity\BattleEntity.h"

class BattleSystem
{
private:
    bool anEntityTurn;
    bool iCrit;
public:
    BattleSystem();
    ~BattleSystem();

    virtual void Update();
    virtual void Render();

    void EntityTurn(BattleEntity* entity);      ///< Give an Entity the Turn

    void Attack(BattleEntity* entity, BattleEntity* targetEntity);  ///< Attack the targetEntity

    PartySystem* playerParty;                   ///< Get the player's Party
    std::list<BattleEntity*> BattleList;

};

#endif /* BATTLESYSTEM_H */