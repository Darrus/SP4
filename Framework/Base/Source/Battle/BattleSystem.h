#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include <list>

#include "..\Character\CharacterInfo.h"
#include "..\Player\Player.h"
#include "..\Entity\BattleEntity.h"
#include "..\Entity\SpriteEntity.h"
#include "..\EnemyAI.h"
#include "..\BattleLog.h"
#include "..\Skills\Skill.h"

class BattleSystem
{
private:
    bool anEntityTurn;
    bool iCrit, iDodge;
    SpriteEntity* CommandBox;
    bool isPassTurn;
    bool battleEnded;
    BattleEntity* pewpewpew;
    SpriteEntity* Arrow;
    EnemyAI* enemyAI;
    Skill* skills;
    PartySystem* partypew;
    bool addEXP;

public:
    BattleSystem();
    BattleSystem(BattleEntity* entity);
    //BattleSystem();
    ~BattleSystem();

    virtual void Update();
    virtual void Render();
    virtual void Exit();

    void RenderEntities();
    void RenderUIStuff();

    // Choosing Target and finding stuff
    BattleEntity* ChooseAtkTarget(BattleEntity* entity);
    BattleEntity* ChooseAtkTarget(int selection);
    BattleEntity* FindTarget(int selection);
    BattleEntity* CheckAnyAlive();

    ///< Battle Command Moves
    void EntityTurn(BattleEntity* entity);      ///< Give an Entity the Turn
    void Attack(BattleEntity* entity, BattleEntity* targetEntity);  ///< Attack the targetEntity
    void SpellCast(BattleEntity* entity, BattleEntity* targetEntity);  ///< Attack the targetEntity
    void Defend(BattleEntity* entity);
    void PassTurn(BattleEntity* entity);
    void FleeBattle();
    void ResetATB(BattleEntity* entity);

    ///< Battle Checks
    void CheckCrit(float critRate);             ///< Function to check if player crits
    void CheckDodge(float dodgeRate);           ///< Function to check if player dodges
    bool getBattleStatus() { return battleEnded; }
    void checkEnemyDead();

    ///< User Inputs
    void ChoosePlayerInput();

    ///< Show Battle Results
    void ShowBattleResults();

    // Assigning Party
    void AssignPlayerParty(PartySystem* party);

    PartySystem* playerParty;                   ///< Get the player's Party
    SpriteEntity* BattleSprites;                ///< Battle Sprites

    std::list<BattleEntity*> BattleList;        ///< List to store all battle entities
    std::list<BattleEntity*> EnemyList;         ///< Store Enemy Data
    std::list<BattleEntity*> PlayerList;        ///< Store Player Data
    std::list<SpriteEntity*> SpriteList;        ///< Store Battle Sprites

    // U.I. Stuff, in testintg
    int selection[5];
    int playerselect;
    int attkselect;
    int commandselect;
    int skillselect;

    enum SELECTIONAT
    {
        NOTHING = 0,
        CHOOSEPLAYER,
        CHOOSETARGET,
        CHOOSESKILL,
        CHOOSEDOWAT,
    };
    SELECTIONAT whichScreen;
    void GetInputSelection(BattleEntity* entity, SELECTIONAT screen, int selection);
}; 

#endif /* BATTLESYSTEM_H */