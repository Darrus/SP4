#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include <list>

#include "GraphicsManager.h"
#include "../Application.h"

#include "..\Character\CharacterInfo.h"
#include "..\Character\EnemyInfo.h"
#include "..\Player\Player.h"
#include "..\Entity\BattleEntity.h"
#include "..\Entity\SpriteEntity.h"
#include "..\EnemyAI.h"
#include "..\BattleLog.h"

class BattleSystem
{
private:
    bool anEntityTurn;                                                          ///< Boolean to check if it's an Entitys' Turn
    bool iCrit, iDodge;                                                         ///< Boolean to check if Unit Crit/Dodged
    SpriteEntity* CommandBox;                                                   ///< Sprite Entity for the Command Box
    bool isPassTurn;                                                            ///< Boolean to check if the Entity passed the turn
    bool battleEnded;                                                           ///< Boolean to check if battle has ended
    BattleEntity* pewpewpew;                                                    ///< Temporary Battle entity storage for players/enemies
    SpriteEntity* Arrow;                                                        ///< Sprite Entity for the Arrow
    EnemyAI* enemyAI;                                                           ///< Handles the A.I. of the enemy.
    bool addEXP;                                                                ///< Boolean to check if EXP is added
    CharacterInfo* playerInfo;                                                  ///< Character Info's such as stats, HP, EXP
    bool chooseItem;
    int turnPt;
    bool noMoreItems;
    bool choosingSkill;
    bool escapeAnot;
    float temp = 0;
    bool input;
    int EXPGAIN;
    int playerPartySize, enemyStart, enemyEnd;
    int tempCast;
	int id;

    MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
    float windowWidth = (float)Application::GetInstance().GetWindowWidth();
    float windowHeight = (float)Application::GetInstance().GetWindowHeight();

	inline int GetID() { return id++; }

public:
    BattleSystem();                                                             ///< Default Constructor
    BattleSystem(BattleEntity* entity);                                         ///< Overloaded Constructor which takes in a Battle Entity
    ~BattleSystem();                                                            ///< Destructor

    virtual void Update();                                                      ///< virtual Update as for Polymorphism, only want to call this class's Update
    virtual void Render();                                                      ///< virtual Render as for Polymorphism, only want call this class's Render
    virtual void Exit();                                                        ///< virtual Exit as for Polymorphism, only want call this class's Exit

    ///< Rendering User Interfaces
    void RenderEntities();                                                      ///< For Rendering the Entities such as Players and Enemies
    void RenderUIStuff();                                                       ///< For Rendering User Interface such as Command Box, Turn Bar, Selection Arrow
    void RenderInventory();
    void RenderATB();
    void RenderNameHP();
    void RenderSkillInterface();
    void RenderBattleInterface();
    void RenderTargetChoose();

    ///< Choosing Target and checking if entity is alive
    BattleEntity* ChooseAtkTarget(int selection);                               ///< Returns a Target for the player to attack base on the selection
    BattleEntity* FindTarget(int selection);                                    ///< Returns a 
    BattleEntity* CheckAnyAlive();

    ///< Battle Command Moves
    void EntityTurn(BattleEntity* entity);      ///< Give an Entity the Turn
    void Attack(BattleEntity* entity, BattleEntity* targetEntity);  ///< Attack the targetEntity
    void SpellCast(BattleEntity* entity);  ///< Attack the targetEntity
    void Defend(BattleEntity* entity);
    void PassTurn(BattleEntity* entity);
    bool FleeBattle(int playerLevel);

    ///< Battle Checks
    void CheckCrit(float critRate);             ///< Function to check if player crits
    void CheckDodge(float dodgeRate);           ///< Function to check if player dodges
    bool getBattleStatus() { return battleEnded; }
    void checkEnemyDead();
    void ResetATB(BattleEntity* entity);

    ///< User Inputs
    void ChoosePlayerInput();
    void ChooseItems(BattleEntity* entity);
    EnemyInfo* ChooseSkillTarget();
    CharacterInfo* ChooseSkillTargetP();

    ///< Show Battle Results
    void ShowBattleResults();
    void DefeatGameOver();
    void EscapeBattle();

    ///< Battle End Check
    void CheckBattleEnd(BattleEntity* entity);

    ///< Check
    void NoMoreItems();

    // Assigning Party
    void AssignPlayerParty();
    void AssignEnemies();

    //CharacterInfo* playerInfo;                   ///< Get the player's Party
    SpriteEntity* BattleSprites;                ///< Battle Sprites

    std::list<BattleEntity*> BattleList;        ///< List to store all battle entities
    std::list<BattleEntity*> EnemyList;         ///< Store Enemy Data
    std::list<BattleEntity*> PlayerList;        ///< Store Player Data
    std::list<SpriteEntity*> SpriteList;        ///< Store Battle Sprites
    std::list<CharacterInfo*> PlayerInfoList;
    std::list<EnemyInfo*> EnemyInfoList;

    // U.I. Stuff, in testintg
    int playerselect;
    int attkselect;
    int commandselect;
    int skillselect;
    int itemselect;

    PartySystem* partypew;                                                      ///< The Player's Party

    enum SELECTIONAT
    {
        NOTHING = 0,
        CHOOSEPLAYER,
        CHOOSETARGET,
        CHOOSESKILL,
        CHOOSEDOWAT,
        CHOOSEITEM,
        CHOOSESKILLTP,
        CHOOSESKILLTE,
    };
    SELECTIONAT whichScreen;
    void GetInputSelection(BattleEntity* entity, SELECTIONAT screen, int selection);
}; 

#endif /* BATTLESYSTEM_H */