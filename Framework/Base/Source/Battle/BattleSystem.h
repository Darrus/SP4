#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include <list>

#include "..\Character\CharacterInfo.h"
#include "..\Party\PartySystem.h"
#include "..\Entity\BattleEntity.h"
#include "..\Entity\SpriteEntity.h"

class BattleSystem
{
private:
    bool anEntityTurn;
    bool iCrit;
    SpriteEntity* CommandBox;

public:
    BattleSystem();
    //BattleSystem();
    ~BattleSystem();

    virtual void Update();
    virtual void Render();

    BattleEntity* ChooseAtkTarget(BattleEntity* entity);

    void EntityTurn(BattleEntity* entity);      ///< Give an Entity the Turn

    void Attack(BattleEntity* entity, BattleEntity* targetEntity);  ///< Attack the targetEntity
    void SpellCast(BattleEntity* entity, BattleEntity* targetEntity);  ///< Attack the targetEntity
    void Defend(BattleEntity* entity);
    void PassTurn(BattleEntity* entity);

    PartySystem* playerParty;                   ///< Get the player's Party
    std::list<BattleEntity*> BattleList;

};

#endif /* BATTLESYSTEM_H */