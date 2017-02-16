#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include <list>

#include "..\Character\CharacterInfo.h"
#include "..\Player\Player.h"
#include "..\Entity\BattleEntity.h"
#include "..\Entity\SpriteEntity.h"

class BattleSystem
{
private:
    bool anEntityTurn;
    bool iCrit, iDodge;
    SpriteEntity* CommandBox;
    bool isPassTurn;
    bool battleEnded;
    BattleEntity* pewpewpew;
    //PartySystem party;

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
    
    void ResetATB(BattleEntity* entity);

    void CheckCrit(float critRate);
    void CheckDodge(float dodgeRate);

    bool getBattleStatus() { return battleEnded; }

    void AssignPlayerParty(PartySystem* party);

    PartySystem* playerParty;                   ///< Get the player's Party
    std::list<BattleEntity*> BattleList;
    SpriteEntity* BattleSprites;
    std::list<SpriteEntity*> SpriteList;
}; 

#endif /* BATTLESYSTEM_H */