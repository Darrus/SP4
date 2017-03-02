#include "BattleSystem.h"
#include "../Entity/EntityFactory.h"

#include "KeyboardController.h"
#include "SceneManager.h"
#include "..\Battle\MonsterFactory.h"

#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"

#include "..\Overworld\Overworld.h"
#include "..\Player\Player.h"
#include "..\Skills\Skill.h"
#include "timer.h"

/***************************************
///< Default constructor
A Default constructor for the Battle System, sets parameters here
*****************************************/
BattleSystem::BattleSystem() :
anEntityTurn(false),
iCrit(false),
isPassTurn(false),
battleEnded(false),
iDodge(false),
playerselect(0),
attkselect(0),
commandselect(0),
skillselect(0),
whichScreen(NOTHING),
addEXP(false),
turnPt(0),
chooseItem(false),
itemselect(0),
noMoreItems(false), 
choosingSkill(false),
escapeAnot(false),
input(false),
EXPGAIN(0),
tempCast(0),
id(0),
checkGO(false)
{
    float windowWidth = (float)Application::GetInstance().GetWindowWidth();
    float windowHeight = (float)Application::GetInstance().GetWindowHeight();

    MeshBuilder::GetInstance()->GenerateCube("HealthBar", Color(0, 1, 0), 1.f);
    MeshBuilder::GetInstance()->GenerateCube("RedBar", Color(1, 0, 0), 1.f);

    CommandBox = new SpriteEntity(MeshBuilder::GetInstance()->GetMesh("Commandselect"));
    CommandBox->SetTextRenderMode(SpriteEntity::MODE_2D);
    CommandBox->SetPosition(Vector3(windowWidth * 0.85f, windowHeight * 0.3f, 10.f));
    CommandBox->SetScale(Vector3(windowWidth * 0.2f, windowHeight * 0.4f, 0.f));

    Arrow = new SpriteEntity(MeshBuilder::GetInstance()->GetMesh("arrow"));
    Arrow->SetTextRenderMode(SpriteEntity::MODE_2D);
    Arrow->SetPosition(Vector3(windowWidth * 0.85f, windowHeight * 0.3f, 10.f));
    Arrow->SetScale(Vector3(windowWidth * 0.05f, windowHeight * 0.05f, 0.f));

    // Player Battle Sprites
    //SetPosition((Vector3(windowWidth * 0.75f, windowHeight * (0.1f * (i + 1.5)), 1.f)));
    BattleSprites = new SpriteEntity(MeshBuilder::GetInstance()->GetMesh("player1"));
    BattleSprites->SetTextRenderMode(SpriteEntity::MODE_2D);
    BattleSprites->SetPosition(Vector3(windowWidth * 0.75f, windowHeight * 0.3f, 1.f));
    BattleSprites->SetScale(Vector3(windowWidth * 0.1f, windowHeight * 0.1f, 0.f));
    SpriteList.push_back(BattleSprites);
    BattleSprites = nullptr;

    BattleSprites = new SpriteEntity(MeshBuilder::GetInstance()->GetMesh("player2"));
    BattleSprites->SetTextRenderMode(SpriteEntity::MODE_2D);
    BattleSprites->SetPosition(Vector3(windowWidth * 0.75f, windowHeight * 0.45f, 1.f));
    BattleSprites->SetScale(Vector3(windowWidth * 0.1f, windowHeight * 0.1f, 0.f));
    SpriteList.push_back(BattleSprites);
    BattleSprites = nullptr;

    BattleSprites = new SpriteEntity(MeshBuilder::GetInstance()->GetMesh("player3"));
    BattleSprites->SetTextRenderMode(SpriteEntity::MODE_2D);
    BattleSprites->SetPosition(Vector3(windowWidth * 0.75f, windowHeight * 0.6f, 1.f));
    BattleSprites->SetScale(Vector3(windowWidth * 0.1f, windowHeight * 0.1f, 0.f));
    SpriteList.push_back(BattleSprites);
    BattleSprites = nullptr;

    enemyAI = new EnemyAI();

    //enemyAI->battlelog = new BattleLog();
    //enemyStart = (Player::GetInstance().GetParty()->memberCount());
    //enemyEnd = ((Player::GetInstance().GetParty()->memberCount()) + (EnemyList.size() - 1));
}

/***************************************
///< destructor
A Default constructor for the Battle System, sets parameters here
*****************************************/
BattleSystem::~BattleSystem()
{

}

/***************************************
///< Update
Battle System Update, It checks through the whole list of Entities and Updates their attack bar
It gives the Unit who filled their bar up first, and stops all other bar updates
*****************************************/
void BattleSystem::Update()
{
    //int playerPartySize = (Player::GetInstance().GetParty()->memberCount() - 1); // start from 0
    //if (!battlelog->Update())
    enemyAI->battlelog->Update();
    playerPartySize = (Player::GetInstance().GetParty()->memberCount());
    //enemyStart = (Player::GetInstance().GetParty()->memberCount());
    //enemyEnd = ((Player::GetInstance().GetParty()->memberCount()) + (EnemyList.size() - 1));
    enemyStart = 4;
    enemyEnd = enemyStart + EnemyList.size() + 1;

    if (escapeAnot)
        EscapeBattle();
    else
    {
        // Loops through the entire EnemyList and do stuff
        for (std::list<BattleEntity*>::iterator itr = EnemyList.begin(); itr != EnemyList.end(); itr++)
        {
            if (!(*itr)->GetReady())
                (*itr)->Update(); ///< Updates the enemy ATB;
            else
            {
                BattleEntity* test = FindTarget(Math::RandIntMinMax(0, playerPartySize - 1));

                if (test->GetHP() > 0)
                {
                    enemyAI->DetermineAction((*itr), test);
                }
                else
                    test = FindTarget(Math::RandIntMinMax(0, 2));
            }
        }

        // Loops through the entire PlayerList and do stuff
        for (std::list<BattleEntity*>::iterator itr = PlayerList.begin(); itr != PlayerList.end(); itr++)
        {
            if (CheckAnyAlive() == nullptr)
                CheckBattleEnd((*itr));
            else
            {
                if (CheckAnyPAlive() == nullptr)
                    CheckGameOver();

                if (!(*itr)->GetReady())
                    (*itr)->Update(); ///< Updates the player ATB;
                else
                    input = true;//ChoosePlayerInput();
            }
        }
    }
    if (!escapeAnot)
    {
        if (whichScreen == NOTHING)
        {
            if (KeyboardController::GetInstance()->IsKeyPressed(VK_DOWN))
            {
                playerselect--;
            }
            if (KeyboardController::GetInstance()->IsKeyPressed(VK_UP))
            {
                playerselect++;
            }
            if (playerselect > playerPartySize - 1)
                playerselect = 0;
            if (playerselect < 0)
                playerselect = playerPartySize - 1;
        }
        if (input)
            ChoosePlayerInput();

        if (commandselect < 0)
            commandselect = 4;
        if (commandselect >= 5)
            commandselect = 0;

        if (ChooseAtkTarget(attkselect) == nullptr)
            attkselect++;

        if (ChooseAtkTarget(attkselect) != nullptr)
        {
            if (ChooseAtkTarget(attkselect)->GetHP() <= 0)
                attkselect++;
        }

        if (attkselect > enemyEnd)
            attkselect = enemyStart;
        if (attkselect < enemyStart)
            attkselect = enemyEnd;
    }
}

void BattleSystem::CheckBattleEnd(BattleEntity* entity)
{
    if (!addEXP)
    {
        for (int i = 0; i < playerPartySize; i++)
        {
            //Player::GetInstance().GetParty()->GetMemberByIndex(i)->stats.Getlevel()
            EXPGAIN = (int)((double)(EnemyList.size() * PlayerList.size()) * ((double)Player::GetInstance().GetParty()->GetMemberByIndex(i)->stats.Getlevel()));

			Player::GetInstance().GetParty()->GetMemberByIndex(i)->EXP += EXPGAIN;

			if (Player::GetInstance().GetParty()->GetMemberByIndex(i)->stats.Getlevel() < 100)
            {
				Player::GetInstance().GetParty()->GetMemberByIndex(i)->CheckLevelUp();
            }
			else if (Player::GetInstance().GetParty()->GetMemberByIndex(i)->stats.Getlevel() >= 100)
            {
				int testy = Player::GetInstance().GetParty()->GetMemberByIndex(i)->stats.Getlevel() - 100;
				Player::GetInstance().GetParty()->GetMemberByIndex(i)->stats.DeductLevel(testy);
            }

			Player::GetInstance().GetParty()->GetMemberByIndex(i)->stats.UpdateStats();
        }
        addEXP = true;
		id = 0;
    }
    if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
    {
        Overworld::battle = false;
        addEXP = false;
		id = 0;
        Player::GetInstance().DoDie();

        for (std::list<BattleEntity*>::iterator itr = EnemyList.begin(); itr != EnemyList.end(); itr++)
        {
            ResetATB(*itr);
        }

        // Loops through the entire PlayerList and do stuff
        for (std::list<BattleEntity*>::iterator itr = PlayerList.begin(); itr != PlayerList.end(); itr++)
        {
            enemyAI->ResetAIBar((*itr));
        }

        SceneManager::GetInstance()->PreviousScene();
        anEntityTurn = false;
        isPassTurn = false;
        iCrit = false;
        whichScreen = NOTHING;
        input = false;
        enemyAI->battlelog->battleloglist.clear();
    }
}

void BattleSystem::CheckGameOver()
{
    checkGO = true;
    if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
    {
        Overworld::battle = false;
        addEXP = false;
        checkGO = false;
        id = 0;
        Player::GetInstance().DoDie();

        for (std::list<BattleEntity*>::iterator itr = EnemyList.begin(); itr != EnemyList.end(); itr++)
        {
            ResetATB(*itr);
        }

        // Loops through the entire PlayerList and do stuff
        for (std::list<BattleEntity*>::iterator itr = PlayerList.begin(); itr != PlayerList.end(); itr++)
        {
            enemyAI->ResetAIBar((*itr));
        }
        anEntityTurn = false;
        isPassTurn = false;
        iCrit = false;
        whichScreen = NOTHING;
        input = false;
        enemyAI->battlelog->battleloglist.clear();

        SceneManager::GetInstance()->SetActiveScene("MainMenuScene");
    }
}

void BattleSystem::ChoosePlayerInput()
{
    if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE) && FindTarget(playerselect)->GetReady() && !anEntityTurn && whichScreen == NOTHING && !FindTarget(playerselect)->GetDead())
    {
        whichScreen = CHOOSEPLAYER;
    }

    GetInputSelection(FindTarget(playerselect), whichScreen, playerselect);
}

/***************************************
///< ChooseAtkTarget
Chooses a Target to return to the player

///< param BattleEntity* entity
Passes in the entity to cross-check that it doesn't return itself and attack itself

///< param int selection
chooses the target

///< returns (*itr)
Returns an Entity for the target to attack.
*****************************************/
BattleEntity* BattleSystem::ChooseAtkTarget(int selection)
{
    for (std::list<BattleEntity*>::iterator itr = EnemyList.begin(); itr != EnemyList.end(); itr++)
    {
        if ((*itr)->GetInfo()->id == selection)
        {
            return (*itr);
        }
    }
    return nullptr;
}

BattleEntity* BattleSystem::CheckAnyAlive()
{
    for (std::list<BattleEntity*>::iterator itr = EnemyList.begin(); itr != EnemyList.end(); itr++)
    {
        if (!(*itr)->GetDead())
        {
            return (*itr);
        }
    }
    return nullptr;
}

BattleEntity* BattleSystem::CheckAnyPAlive()
{
    for (std::list<BattleEntity*>::iterator itr = PlayerList.begin(); itr != PlayerList.end(); itr++)
    {
        if ((*itr)->GetHP() > 0)
        {
            return (*itr);
        }
    }
    return nullptr;
}

BattleEntity* BattleSystem::FindTarget(int selection)
{
     for (std::list<BattleEntity*>::iterator itr = PlayerList.begin(); itr != PlayerList.end(); itr++)
    {
         if ((*itr)->id == selection)
        {
            return (*itr);
        }
    }
    return nullptr;
}

/***************************************
///< EntityTurn
Gives the Entity that it received the turn, able to choose what commands to do

///< param entity
Passes in the entity that gets the turn
*****************************************/
void BattleSystem::EntityTurn(BattleEntity* entity)
{
    if (entity->GetAttkTurnPt() > 0 && !isPassTurn)
    {
        whichScreen = CHOOSEDOWAT;
        turnPt = entity->GetAttkTurnPt();
    }
}

/***************************************
///< Attack
Entity Attacks another Entity, and do following calculations

///< param entity
The entity that unleashes the attack

///< param targetEntity
Target Entity which the Entity chosed to attack.
*****************************************/
void BattleSystem::Attack(BattleEntity* entity, BattleEntity* targetEntity)
{
    InfoBase* myEntity = entity->GetInfo();
    InfoBase* targEntity = targetEntity->GetInfo();

    myEntity->stats.GetCritRate();
    if (targetEntity != nullptr)
    {
        int DamageDeal;
        CheckCrit(myEntity->stats.GetCritRate());
        CheckDodge(targEntity->stats.GetDodgeRate());
        if (!iDodge)
        {
            if (iCrit)
            {
                DamageDeal = (int)(((double)myEntity->stats.GetDamage() * 1.5) - (double)((float)targEntity->stats.GetDefence() * targetEntity->GetDefending()));
                if (DamageDeal <= 0)
                    DamageDeal = 0;
            }
            else
            {
                DamageDeal = myEntity->stats.GetDamage() - (int)((float)targEntity->stats.GetDefence() * targetEntity->GetDefending());
                if (DamageDeal <= 0)
                    DamageDeal = 0;
            }
            targetEntity->TakeDamage(DamageDeal);
            enemyAI->battlelog = new BattleLog(targetEntity, myEntity->name, DamageDeal, DamageDeal, iDodge, iCrit);
            enemyAI->battlelog->battleloglist.push_back(enemyAI->battlelog);
        }
        else
        {
            DamageDeal = 3;
            enemyAI->battlelog = new BattleLog(targetEntity, myEntity->name, DamageDeal, DamageDeal, iDodge, iCrit);
            enemyAI->battlelog->battleloglist.push_back(enemyAI->battlelog);
        }

        if (targetEntity->GetHP() <= 0)
        {
            targetEntity->GetInfo()->HP = 0;
            battleEnded = true;
        }

        entity->SetDefending(1);
        entity->DecreaseAttkTurnPt(1);

        if (entity->GetAttkTurnPt() > 0)
            whichScreen = CHOOSEDOWAT;
        else
            ResetATB(entity);
    }
}

/***************************************
///< SpellCast
Entity Attacks another Entity, and do following calculations

///< param entity
The entity that unleashes the Spell

///< param targetEntity
Target Entity which the Entity chosed to cast spell on.
*****************************************/
void BattleSystem::SpellCast(BattleEntity* entity)
{
    InfoBase* myEntity = entity->GetInfo();
    int i = 0;
	CharacterInfo* chara = dynamic_cast<CharacterInfo*>(FindTarget(playerselect)->GetInfo());
	if (!chara)
		return;

	for (auto itritr = chara->skills.begin(); itritr != chara->skills.end(); ++itritr)
    {
        if (skillselect == i)
        {
            if ((*itritr)->IsAllyTargetable())
            {
                SkillParameters foo;
				foo.caster = chara;
                if ((*itritr)->GetMaxNumberOfTargets() >= 4)
                {
                    for (auto itr = PlayerList.begin(); itr != PlayerList.end(); itr++)
                    {
                        if ((*itr) != nullptr)
                            foo.targetList.push_back((*itr)->GetInfo());
                    }
                    if ((*itritr)->UseSkill(foo))
                    {
                        enemyAI->battlelog = new BattleLog(foo.caster, (*itritr)->GetName(), foo.targetList[0]->name, true);
                        enemyAI->battlelog->battleloglist.push_back(enemyAI->battlelog);
                        choosingSkill = false;
                        entity->DecreaseAttkTurnPt(1);
                        //targEntity->HP - myEntity->stats.GetDamage();

                        if (entity->GetAttkTurnPt() > 0)
                        {
                            whichScreen = CHOOSEDOWAT;
                        }
                        else
                            ResetATB(entity);
                    }
                    else
                    {
                        whichScreen = CHOOSESKILL;
                    }
                }
                else if ((*itritr)->GetMaxNumberOfTargets() <= 1 && (foo.caster->MP >= (*itritr)->GetManaCost()))
                {
                    tempCast = playerselect;
                    whichScreen = CHOOSESKILLTP;
                    choosingSkill = false;
                }
            }
            else if ((*itritr)->IsEnemyTargetable())
            {
                SkillParameters foo;
				foo.caster = chara;

                if ((*itritr)->GetMaxNumberOfTargets() >= 4)
                {
                    for (auto it = EnemyList.begin(); it != EnemyList.end(); it++)
                    {
                        if ((*it) != nullptr)
                            foo.targetList.push_back((*it)->GetInfo());
                    }

                    if ((*itritr)->UseSkill(foo))
                    {
                        enemyAI->battlelog = new BattleLog(foo.caster, (*itritr)->GetName(), foo.targetList[0]->name, true);
                        enemyAI->battlelog->battleloglist.push_back(enemyAI->battlelog);
                        choosingSkill = false;
                        entity->DecreaseAttkTurnPt(1);
                        //targEntity->HP - myEntity->stats.GetDamage();

                        if (entity->GetAttkTurnPt() > 0)
                        {
                            whichScreen = CHOOSEDOWAT;
                        }
                        else
                            ResetATB(entity);
                    }
                    else
                    {
                        whichScreen = CHOOSESKILL;
                    }
                }
                else if ((*itritr)->GetMaxNumberOfTargets() <= 1 && (foo.caster->MP >= (*itritr)->GetManaCost()))
                {
                    whichScreen = CHOOSESKILLTE;
                    choosingSkill = false;
                }
            }
        }
        ++i;
    }
}


EnemyInfo* BattleSystem::ChooseSkillTarget()
{
    for (auto it = EnemyInfoList.begin(); it != EnemyInfoList.end(); it++)
    {
        if ((*it)->id == attkselect && (*it) != nullptr)
            return (*it);
    }
    return nullptr;
}

CharacterInfo* BattleSystem::ChooseSkillTargetP()
{
    for (int i = 0; i < (Player::GetInstance().GetParty()->memberCount()); ++i)
    {
        if (playerselect == i)
        {
            if (Player::GetInstance().GetParty()->GetMemberByIndex(i) != nullptr)
                return (Player::GetInstance().GetParty()->GetMemberByIndex(i));
        }
    }
    return nullptr;
}

/***************************************
///< CheckCrit
Determine if Entity Crits

///< param critRate
passes in Crit Rate of Entity
*****************************************/
void BattleSystem::CheckCrit(float critRate)
{
    float critcrit = 0.f;
    if (critRate >= 80.f)
        critcrit = 80.f;
    else
        critcrit = critRate;

    if (critcrit >= (Math::RandFloatMinMax(0, 100)))
        iCrit = true;
    else
        iCrit = false;
}

/***************************************
///< CheckDodge
Determine if Entity Dodges

///< param dodgeRate
passes in Dodge Rate of Entity
*****************************************/
void BattleSystem::CheckDodge(float dodgeRate)
{
    float dodgedodge = 0.f;
    if (dodgeRate >= 80.f)
        dodgedodge = 80.f;
    else
        dodgedodge = dodgeRate;

    if (dodgedodge >= (Math::RandFloatMinMax(0, 100)))
        iDodge = true;
    else
        iDodge = false;
}

/***************************************
///< Defend
Entity Defends, taking reduced damage and gaining an attack turn point

///< param entity
Entity that is defending
*****************************************/
void BattleSystem::Defend(BattleEntity* entity)
{ 
    entity->SetDefending(1.5);
    enemyAI->battlelog = new BattleLog(entity, true);
    enemyAI->battlelog->battleloglist.push_back(enemyAI->battlelog);
    PassTurn(entity);
    //entity->DecreaseAttkTurnPt(1);
}

/***************************************
///< Pass Turn
Basically Adds A turn Point to the unit
///< param entity
The entity that defended.
*****************************************/
void BattleSystem::PassTurn(BattleEntity* entity)
{
    if (entity->GetAttkTurnPt() >= 5)
        entity->DecreaseAttkTurnPt(1);
    ResetATB(entity);
    isPassTurn = true;
}

/***************************************
///< Flee Battle
Allows the Player to flee the battle
*****************************************/
bool BattleSystem::FleeBattle(int playerLevel)
{
    bool successRate = false;
    if (playerLevel < CheckAnyAlive()->GetInfo()->stats.Getlevel())
        successRate = true;
    else
        successRate = false;

    
    if (((successRate + 1) * 3) >= Math::RandIntMinMax(0, 12))
    {
        enemyAI->battlelog = new BattleLog(true);
        enemyAI->battlelog->battleloglist.push_back(enemyAI->battlelog);
        id = 0;
        return true;
    }
    else
    {
        enemyAI->battlelog = new BattleLog(false);
        enemyAI->battlelog->battleloglist.push_back(enemyAI->battlelog);
        return false;
    }
}

/***************************************
///< ResetATB
Whenever a unit casts finished a command, the Attack Bar will reset, will only cast if it has no more Turn Point or it Defended.
///< param entity
The entity that has used up all turn point or defended.
*****************************************/
void BattleSystem::ResetATB(BattleEntity* entity)
{
    entity->SetATB(0.0);
    entity->GetInfo()->stats.UpdateStats();
    entity->SetReady(false);
    anEntityTurn = false;
    isPassTurn = false;
    iCrit = false;
    input = false;
    whichScreen = NOTHING;
    commandselect = 0;
    skillselect = 0;
    itemselect = 0;
}

/***************************************
///< Render
Renders All the current entities inside the Battle List.
*****************************************/
void BattleSystem::Render()
{
    if (checkGO)
        RenderGameOver();
    else
    {
        if (CheckAnyAlive() == nullptr)
            ShowBattleResults();
        else
        {
            enemyAI->battlelog->Render();

            if (Overworld::battle != false)
            {
                if (!escapeAnot)
                    RenderUIStuff();

                RenderEntities();
                //battlelog->Render();
                if (chooseItem == true)
                    RenderInventory();
                if (noMoreItems == true)
                    NoMoreItems();
            }
        }
    }
}

void BattleSystem::RenderGameOver()
{
    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * 0.5f, windowHeight * 0.5f, 8.0f);
    modelStack.Scale(windowWidth *0.8f, windowHeight * 0.8f, 1.f);
    RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Commandselect"));
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * 0.2f, windowHeight * 0.5f, 9.f);
    modelStack.Scale(70.f, 70.f, 1.f);
    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "GAME OVER", Color(0, 1, 0));
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * 0.2f, windowHeight * 0.4f, 9.f);
    modelStack.Scale(50.f, 50.f, 1.f);
    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Your Party has been wiped", Color(0, 1, 0));
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * 0.2f, windowHeight * 0.2f, 9.f);
    modelStack.Scale(50.f, 50.f, 1.f);
    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Press Spacebar to go back to Menu.", Color(0, 1, 0));
    modelStack.PopMatrix();
}

void BattleSystem::NoMoreItems()
{
    float dt = (float)StopWatch::GetInstance()->GetDeltaTime();

    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * 0.45f, windowHeight * 0.7f, 5.f);
    modelStack.Scale(30, 30, 1.f);
    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "NO MORE ITEMS", Color(0, 1, 0));
    modelStack.PopMatrix();

    temp += dt;
    if (temp > 3.f)
    {
        temp = 0.f;
        noMoreItems = false;
    }
}

void BattleSystem::RenderUIStuff()
{
    float TEXTSCALE = 35.f;

    switch (whichScreen)
    {
    case NOTHING:
        for (int i = 0; i < playerPartySize; ++i)
        {
            if (playerselect == i)
                Arrow->SetPosition((Vector3(windowWidth * 0.85f, windowHeight * (0.3f + ((i)* 0.15f)), 1.f)));
                //Arrow->SetPosition(Vector3(windowWidth * 0.8f, windowHeight * (0.25f + (0.15f * i)), 10.f));

        }
        break;
    case CHOOSESKILLTP:
    {
        for (int i = 0; i < playerPartySize; ++i)
        {
            if (playerselect == i)
                Arrow->SetPosition((Vector3(windowWidth * 0.85f, windowHeight * (0.3f + ((i)* 0.15f)), 1.f)));
        }
        RenderTargetChoose();
    }
        break;
    case CHOOSETARGET:
    {
                         int p = 0;
        for (int i = enemyStart; i < enemyEnd; i++)
        {
            if (attkselect == i)
                Arrow->SetPosition(Vector3(windowWidth * 0.35f, windowHeight * (0.09f * (i - 1 + p)), 5.f));
            p++;
        }
        
        RenderTargetChoose();
    }
        break;
    case CHOOSESKILLTE:
    {
                          int p = 0;
        for (int i = enemyStart; i < enemyEnd; i++)
        {
            if (attkselect == i)
                Arrow->SetPosition(Vector3(windowWidth * 0.35f, windowHeight * (0.09f * (i - 1 + p)), 5.f));
            p++;
        }//0.3, 0.5, 0.7
        
        RenderTargetChoose();
    }
        break;
    case CHOOSEDOWAT:
    {
        float DIST = 0.95f;
        for (int i = 0; i < 5; ++i)
        {
            if (commandselect == i)
                Arrow->SetPosition(Vector3(windowWidth * DIST, windowHeight * (0.65f - (0.05f * i)), 10.f));
        }
    }
    break;
    case CHOOSESKILL:
        RenderSkillInterface();
        break;
    }

    if (anEntityTurn && !escapeAnot && whichScreen != CHOOSESKILLTP && whichScreen != CHOOSESKILLTE)
        RenderBattleInterface();

    Arrow->RenderUI();
}

void BattleSystem::RenderTargetChoose()
{
    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * 0.5f, windowHeight * 0.75f, 5.f);
    modelStack.Scale(windowWidth *0.2f, windowHeight *0.1f, 1.f);
    RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Commandselect"));
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * 0.425f, windowHeight * 0.75f, 8.f);
    modelStack.Scale(25.f, 25.f, 1.f);
    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Choose A Target", Color(0, 1, 0));
    modelStack.PopMatrix();
}

void BattleSystem::RenderSkillInterface()
{
    int i = 0;
    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * 0.65f, windowHeight * 0.5f, 8.f);
    modelStack.Scale(windowWidth *0.3f, windowHeight *0.5f, 1.f);
    RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Commandselect"));
    modelStack.PopMatrix();

    for (auto itritr = PlayerList.begin(); itritr != PlayerList.end(); itritr++)
    {
        if ((*itritr)->GetInfo()->id == playerselect)
        {
            modelStack.PushMatrix();
            modelStack.Translate(windowWidth * 0.5f, windowHeight *  0.7f, 8.5f);
            modelStack.Scale(30.f, 30.f, 1.f);
            RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "MP: " + std::to_string((*itritr)->GetInfo()->MP) + " / " + std::to_string((*itritr)->GetInfo()->stats.GetMaxMP()), Color(0, 1, 0));
            modelStack.PopMatrix();
        }
    }

	CharacterInfo *pewchara = dynamic_cast<CharacterInfo*>(FindTarget(playerselect)->GetInfo());

	///< Arrow
    float DIST = 0.65;
    for (int i = 0; i < (pewchara->skills.size()); i++)
        if (skillselect == i)
            Arrow->SetPosition(Vector3(windowWidth * 0.8f, windowHeight * (DIST - (0.05f * i)), 10.f));


    for (auto itritr = pewchara->skills.begin(); itritr != pewchara->skills.end(); ++itritr)
    {
        modelStack.PushMatrix();
        modelStack.Translate(windowWidth * 0.5f, windowHeight *  (DIST + (i * -0.05f)), 8.5f);
        modelStack.Scale(30.f, 30.f, 1.f);
        RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*itritr)->GetName() + " - Cost: " + std::to_string((*itritr)->GetManaCost()), Color(0, 1, 0));
        modelStack.PopMatrix();
        ++i;
    }
}

void BattleSystem::RenderBattleInterface()
{
    float TEXTSCALE = 35.f;
    float FIRSTONE = 0.65f;
    float WIDTHSCALE = 0.85f;
    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * 0.9f, windowHeight * 0.55f, 5.f);
    modelStack.Scale(windowWidth *0.15f, windowHeight *0.4f, 1.f);
    RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Commandselect"));
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * WIDTHSCALE, windowHeight * 0.7f, 5.f);
    modelStack.Scale(TEXTSCALE, TEXTSCALE, 1.f);
    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Turn Pt: " + std::to_string(turnPt), Color(0, 1, 0));
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * WIDTHSCALE, windowHeight * FIRSTONE, 5.f);
    modelStack.Scale(TEXTSCALE, TEXTSCALE, 1.f);
    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Attack", Color(0, 1, 0));
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * WIDTHSCALE, windowHeight * (FIRSTONE - 0.05f), 5.f);
    modelStack.Scale(TEXTSCALE, TEXTSCALE, 1.f);
    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Defend", Color(0, 1, 0));
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * WIDTHSCALE, windowHeight * (FIRSTONE - 0.1f), 5.f);
    modelStack.Scale(TEXTSCALE, TEXTSCALE, 1.f);
    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Skills", Color(0, 1, 0));
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * WIDTHSCALE, windowHeight * (FIRSTONE - 0.15f), 5.f);
    modelStack.Scale(TEXTSCALE, TEXTSCALE, 1.f);
    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Item", Color(0, 1, 0));
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * WIDTHSCALE, windowHeight * (FIRSTONE - 0.2f), 5.f);
    modelStack.Scale(TEXTSCALE, TEXTSCALE, 1.f);
    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Flee", Color(0, 1, 0));
    modelStack.PopMatrix();
}

void BattleSystem::RenderEntities()
{
    RenderNameHP();
    RenderATB();

    // Entity Render
    for (std::list<SpriteEntity*>::iterator itr = SpriteList.begin(); itr != SpriteList.end(); itr++)
    {
        (*itr)->RenderUI();
    }

    //int p = 1;
    //for (auto itrrr = PlayerInfoList.begin(); itrrr != PlayerInfoList.end(); itrrr++)
    //{
    //    modelStack.PushMatrix();
    //    modelStack.Translate(windowWidth * 0.75f, windowHeight * (0.15f + (p*0.15f)), 5.f);
    //    modelStack.Scale(150.f, 150.f, 1.f);
    //    ((*itrrr)->anim.Render());
    //    modelStack.PopMatrix();
    //    ++p;
    //}

    //for (auto itrr = PlayerInfoList.begin(); itrr != PlayerInfoList.end(); itrr++)
    //{
    //    (*itrr)->anim.Update();
    //}
}

void BattleSystem::RenderNameHP()
{
    // Bottom Background
    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * 0.5f, windowHeight * 0.125f, 5.f);
    modelStack.Scale(windowWidth, windowHeight *0.25f, 1.f);
    RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Commandselect"));
    modelStack.PopMatrix();

    // Player UI - Name and HP
    for (int i = 0; i < (Player::GetInstance().GetParty()->memberCount()); i++)
    {
        CharacterInfo * charapew = Player::GetInstance().GetParty()->GetMemberByIndex(i);

        modelStack.PushMatrix();
        modelStack.Translate(windowWidth * 0.5, windowHeight * (0.05f * (i + 1)), 5.f);
        modelStack.Scale(35.f, 35.f, 1.f);
        RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), charapew->name + " (HP:" + std::to_string(charapew->HP) + "/" + std::to_string(charapew->stats.GetMaxHP()) + ")(MP:" + std::to_string(charapew->MP) + "/" + std::to_string(charapew->stats.GetMaxMP()) + ")", Color(0, 1, 0));
        modelStack.PopMatrix();
    }
    // Monster UI- Name and HP
    for (std::list<BattleEntity*>::iterator it = EnemyList.begin(); it != EnemyList.end(); it++)
    {
        modelStack.PushMatrix();
        modelStack.Translate(windowWidth * 0.05f, windowHeight * (0.05f * (float)((*it)->GetInfo()->id - 3)), 5.f);
        modelStack.Scale(35.f, 35.f, 1.f);
        RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*it)->GetInfo()->name + " (HP:" + std::to_string((*it)->GetHP()) + "/" + std::to_string((*it)->GetInfo()->stats.GetMaxHP()) + ")", Color(0, 1, 0));
        modelStack.PopMatrix();
    }
}

void BattleSystem::RenderATB()
{
    // Attack Turn Bar
    for (std::list<BattleEntity*>::iterator it = BattleList.begin(); it != BattleList.end(); it++)
    {
        if (!(*it)->GetDead() && !escapeAnot)
        {
            modelStack.PushMatrix();
            modelStack.Translate((*it)->GetPosition().x - 50.f, (*it)->GetPosition().y - 50.f, (*it)->GetPosition().z + 4);
            modelStack.Scale(25.f, 25.f, 1.f);
            RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*it)->GetInfo()->name, Color(0, 1, 0));
            modelStack.PopMatrix();

            modelStack.PushMatrix();
            modelStack.Translate((*it)->GetPosition().x, (*it)->GetPosition().y - 60.f, (*it)->GetPosition().z + 5);
            modelStack.Scale(100.f, 6.f, 1.f);
            RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("RedBar"));
            modelStack.PopMatrix();

            modelStack.PushMatrix();
            modelStack.Translate((*it)->GetPosition().x - Math::Max(0.f, (1 - (*it)->GetATB() / 100.f)) * 50.f, (*it)->GetPosition().y - 60.f, (*it)->GetPosition().z + 6);
            modelStack.Scale((Math::Max(0.f, (*it)->GetATB() / 100.f)) * 100.f, 6.f, 1.f);
            RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("HealthBar"));
            modelStack.PopMatrix();
        }
        int i = 5;
        for (auto itrrr = EnemyInfoList.begin(); itrrr != EnemyInfoList.end(); itrrr++)
        {
            if (!ChooseAtkTarget((*itrrr)->id)->GetDead())
            {
                modelStack.PushMatrix();
                modelStack.Translate(windowWidth * 0.27f, windowHeight * (0.06f *i), 5.f);
                modelStack.Scale(150.f, 150.f, 1.f);
                RenderHelper::RenderMesh((*itrrr)->mesh);
                modelStack.PopMatrix();
            }
            i += 3;
        }
    }
}

void BattleSystem::RenderInventory()
{

    Inventory* pewinventory = Player::GetInstance().GetInventory();
    
    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * 0.65f, windowHeight * 0.5f, 9.f);
    modelStack.Scale(windowWidth *0.3f, windowHeight *0.5f, 1.f);
    RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Commandselect"));
    modelStack.PopMatrix();

    int tempMax = 9;
    int pewpew = 0;

    for (int i = 0; i < (int)(pewinventory->m_inventoryList.size()); ++i)
    {
        float FIRSTONE = 0.65f;
        if (itemselect > tempMax)
        {
            i = itemselect;
            tempMax += 10;
            pewpew = 0;
        }
        if (i < tempMax)
        {
            modelStack.PushMatrix();
            modelStack.Translate(windowWidth * 0.5f, windowHeight * (0.7f + (pewpew * -0.05f)), 9.f);
            modelStack.Scale(35.f, 35.f, 1.f);
            RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), std::to_string(pewpew + 1) + ": " + pewinventory->m_inventoryList[i]->GetName(), Color(0, 1, 0));
            modelStack.PopMatrix();
        }
        pewpew++;
    }

    if (whichScreen == CHOOSEITEM)
    {
        float DIST = 0.75;
        for (unsigned i = 0; i < 9; ++i)
        {
            if (itemselect == i)
                Arrow->SetPosition(Vector3(windowWidth * DIST, windowHeight * (0.7f - (i * 0.05f)), 10.f));
        }
    }
}

void BattleSystem::ShowBattleResults()
{
    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * 0.5f, windowHeight * 0.5f, 8.0f);
    modelStack.Scale(windowWidth *0.8f, windowHeight * 0.8f, 1.f);
    RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Commandselect"));
    modelStack.PopMatrix();
    
    PartySystem* pew = Player::GetInstance().GetParty();
    for (auto it = PlayerInfoList.begin(); it != PlayerInfoList.end(); it++)
    {
        for (int i = 0; i < (Player::GetInstance().GetParty()->memberCount()); ++i)
        {
            modelStack.PushMatrix();
            modelStack.Translate(windowWidth * 0.2f, windowHeight * (0.8f + (i * -0.1f)), 9.f);
            modelStack.Scale(40.f, 40.f, 1.f);
            //if ((*it)->id == i)
                RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), Player::GetInstance().GetParty()->GetMemberByIndex(i)->name + " has Earned: " + std::to_string(EXPGAIN) + " EXP!", Color(0, 1, 0));
            modelStack.PopMatrix();

            modelStack.PushMatrix();
            modelStack.Translate(windowWidth * 0.2f, windowHeight * (0.75f + (i * -0.1f)), 9.f);
            modelStack.Scale(40.f, 40.f, 1.f);
            //if ((*it)->id == i)
                RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"),
                    "EXP: " + std::to_string(Player::GetInstance().GetParty()->GetMemberByIndex(i)->EXP) + " / " + std::to_string(Player::GetInstance().GetParty()->GetMemberByIndex(i)->stats.GetMaxEXP()) + " Lvl : " + std::to_string(Player::GetInstance().GetParty()->GetMemberByIndex(i)->stats.Getlevel()), Color(0, 1, 0));
            modelStack.PopMatrix();
        }
    }

    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * 0.2f, windowHeight * 0.2f, 9.f);
    modelStack.Scale(50.f, 50.f, 1.f);
    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Press Spacebar to Continue.", Color(0, 1, 0));
    modelStack.PopMatrix();
}

/***************************************
///< AssignPlayerParty
passes in the player party to be in the battlelist
*****************************************/
void BattleSystem::AssignPlayerParty()
{
    for (int i = 0; i < (Player::GetInstance().GetParty()->memberCount()); ++i)
    {
        CharacterInfo* MemberInfo = Player::GetInstance().GetParty()->GetMemberByIndex(i);
		if (!MemberInfo)
			continue;

        MemberInfo->stats.UpdateStats();
        if (MemberInfo->HP > 0)
            PlayerInfoList.push_back(MemberInfo);

        pewpewpew = new BattleEntity();
        pewpewpew->enemyType = BattleEntity::ALLY;
        pewpewpew->SetInfo(MemberInfo);

        pewpewpew->SetPosition((Vector3(windowWidth * 0.75f, windowHeight * (0.45f + ((i)* 0.15f)), 1.f)));
		pewpewpew->id = GetID();
        BattleList.push_back(pewpewpew);
        PlayerList.push_back(pewpewpew);
    }
}

/***************************************
///< AssignEnemies
passes in the player party to be in the battlelist
*****************************************/
void BattleSystem::AssignEnemies()
{
    for (auto itr = EnemyInfoList.begin(); itr != EnemyInfoList.end(); itr++)
    {
        EnemyInfo* MonsterInfo = (*itr);
        MonsterInfo->stats.UpdateStats();

        pewpewpew = new BattleEntity();
        pewpewpew->enemyType = BattleEntity::ENEMY;
        pewpewpew->SetInfo(MonsterInfo);

        if (MonsterInfo != nullptr)
        {
            pewpewpew->SetPosition(Vector3(windowWidth * 0.25f, windowHeight * (0.15f * (MonsterInfo->id - 1)), 1.f));
            std::cout << pewpewpew->GetInfo()->id << std::endl;
            BattleList.push_back(pewpewpew);
            EnemyList.push_back(pewpewpew);
        }
    }
}

void BattleSystem::GetInputSelection(BattleEntity* entity, SELECTIONAT screen, int selection)
{
    switch (screen)
    {
    case CHOOSEPLAYER:
        if (!anEntityTurn)
            entity->AddAttkTurnPt(1);

        isPassTurn = false;
        anEntityTurn = true;
        EntityTurn(entity);

        if (KeyboardController::GetInstance()->IsKeyReleased(VK_ESCAPE))
        {
            anEntityTurn = false;
            //anEntityTurn = false;
            input = false;
            entity->DecreaseAttkTurnPt(1);
            whichScreen = NOTHING;
        }
        break;
    case CHOOSETARGET:
        turnPt = entity->GetAttkTurnPt();
        if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
        {
            if (!ChooseAtkTarget(attkselect)->GetDead())
                Attack(entity, ChooseAtkTarget(attkselect));
        }

        if (KeyboardController::GetInstance()->IsKeyReleased(VK_DOWN))
            attkselect--;
        if (KeyboardController::GetInstance()->IsKeyReleased(VK_UP))
            attkselect++;
        if (KeyboardController::GetInstance()->IsKeyReleased(VK_ESCAPE))
        {
            //anEntityTurn = false;
            whichScreen = CHOOSEDOWAT;
        }

        if (ChooseAtkTarget(attkselect) == nullptr)
            attkselect++;

        if (ChooseAtkTarget(attkselect) != nullptr)
        {
            if (ChooseAtkTarget(attkselect)->GetHP() <= 0)
                attkselect++;
        }

        if (attkselect > enemyEnd)
            attkselect = enemyStart;
        if (attkselect < enemyStart)
            attkselect = enemyEnd;

        break;
    case CHOOSEDOWAT:
        if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
        {
            if (commandselect == 0)
                whichScreen = CHOOSETARGET; // Attack
            if (commandselect == 1)
                Defend(entity);             // Defend
            if (commandselect == 2)
                whichScreen = CHOOSESKILL;  // Skill
            if (commandselect == 3)
                whichScreen = CHOOSEITEM;   // Items
            if (commandselect == 4)
                if (!FleeBattle(entity->GetInfo()->stats.Getlevel()))          // Flee
                {
                    ResetATB(entity);
                    entity->DecreaseAttkTurnPt(1);
                }
                else
                    escapeAnot = true;
        }

        if (KeyboardController::GetInstance()->IsKeyPressed(VK_DOWN))
            commandselect++;
        if (KeyboardController::GetInstance()->IsKeyPressed(VK_UP))
            commandselect--;

        if (KeyboardController::GetInstance()->IsKeyPressed(VK_ESCAPE))
        {
            input = false;
            anEntityTurn = false;
            entity->DecreaseAttkTurnPt(1);
            whichScreen = NOTHING;
        }
        break;
	case CHOOSESKILL:
	{
		if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
			choosingSkill = true;

		if (KeyboardController::GetInstance()->IsKeyPressed(VK_DOWN))
			skillselect++;
		if (KeyboardController::GetInstance()->IsKeyPressed(VK_UP))
			skillselect--;

		if (KeyboardController::GetInstance()->IsKeyPressed(VK_ESCAPE))
		{
			whichScreen = CHOOSEDOWAT;
			choosingSkill = false;
		}

		if (KeyboardController::GetInstance()->IsKeyPressed(VK_RIGHT))
		{
			whichScreen = CHOOSEDOWAT;
			choosingSkill = false;
		}

		/* if (skillselect < 0)
			 skillselect = (Player::GetInstance().GetParty()->GetMember(playerselect)->skills.size() - 1);
			 if (skillselect >(Player::GetInstance().GetParty()->GetMember(playerselect)->skills.size() - 1))
			 skillselect = 0;*/

		CharacterInfo* chara = (CharacterInfo*)FindTarget(playerselect)->GetInfo();

		if (skillselect < 0)
		{
			skillselect = chara->skills.size() - 1;
		}
		if (skillselect > chara->skills.size() - 1)
		{
			skillselect = 0;
		}

		if (choosingSkill == true)
			SpellCast(entity);
	}
        break;
    case CHOOSESKILLTE:
    {
        if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
        {
            int i = 0;
            SkillParameters foo;
			CharacterInfo* chara = (CharacterInfo*)FindTarget(playerselect)->GetInfo();
            foo.caster = chara;
            if (ChooseSkillTarget() != nullptr)
            {
				for (auto itritr = chara->skills.begin(); itritr != chara->skills.end(); ++itritr)
                {
                    if (skillselect == i && ChooseSkillTarget()->HP > 0)
                    {
                        foo.targetList.push_back(ChooseSkillTarget());

                        if ((*itritr)->UseSkill(foo))
                        {
                            enemyAI->battlelog = new BattleLog(foo.caster, (*itritr)->GetName(), foo.targetList[0]->name, false);
                            enemyAI->battlelog->battleloglist.push_back(enemyAI->battlelog);
                            choosingSkill = false;
                            //whichScreen = NOTHING;

                            entity->DecreaseAttkTurnPt(1);
                            if (entity->GetAttkTurnPt() > 0)
                            {
                                whichScreen = CHOOSEDOWAT;
                            }
                            else
                                ResetATB(entity);
                        }
                        else
                        {
                            whichScreen = CHOOSESKILL;
                        }

                    }
                    ++i;
                }

            }
        }

        if (KeyboardController::GetInstance()->IsKeyReleased(VK_DOWN))
            attkselect--;
        if (KeyboardController::GetInstance()->IsKeyReleased(VK_UP))
            attkselect++;
        if (KeyboardController::GetInstance()->IsKeyReleased(VK_ESCAPE))
        {
            //anEntityTurn = false;
            whichScreen = CHOOSESKILL;
        }

        if (attkselect > enemyEnd)
            attkselect = enemyStart;
        if (attkselect < enemyStart)
            attkselect = enemyEnd;
        break;
    }
    case CHOOSESKILLTP:
    {
        if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
        {
            int i = 0;
            SkillParameters foo;
			CharacterInfo* chara = (CharacterInfo*)FindTarget(tempCast)->GetInfo();
            foo.caster = chara;

            if (ChooseSkillTarget() != nullptr)
            {
				for (auto itritr = chara->skills.begin(); itritr != chara->skills.end(); ++itritr)
                {
                    if (skillselect == i && ChooseSkillTargetP()->HP > 0)
                    {
                        foo.targetList.push_back(ChooseSkillTargetP());

                        if ((*itritr)->UseSkill(foo))
                        {
                            enemyAI->battlelog = new BattleLog(foo.caster, (*itritr)->GetName(), foo.targetList[0]->name, false);
                            enemyAI->battlelog->battleloglist.push_back(enemyAI->battlelog);
                            choosingSkill = false;
                            //whichScreen = NOTHING;
                            FindTarget(tempCast)->DecreaseAttkTurnPt(1);

                            if (FindTarget(tempCast)->GetAttkTurnPt() > 0)
                            {
                                whichScreen = CHOOSEDOWAT;
                            }
                            else
                                ResetATB(FindTarget(tempCast));
                        }
                        else
                        {
                            whichScreen = CHOOSESKILL;
                        }
                    }
                    ++i;
                }

            }
        }

        if (KeyboardController::GetInstance()->IsKeyReleased(VK_DOWN))
            playerselect--;
        if (KeyboardController::GetInstance()->IsKeyReleased(VK_UP))
            playerselect++;
        if (KeyboardController::GetInstance()->IsKeyReleased(VK_ESCAPE))
        {
            //anEntityTurn = false;
            whichScreen = CHOOSESKILL;
        }

        if (playerselect >  playerPartySize - 1)
            playerselect = 0;
        if (playerselect < 0)
            playerselect = playerPartySize - 1;
        break;
    }
    case CHOOSEITEM:
        chooseItem = true;
        ChooseItems(entity);
        break;
    }
}

void BattleSystem::EscapeBattle()
{
    temp += (float)StopWatch::GetInstance()->GetDeltaTime();
    if (temp >= 3.f)
    {
        EnemyList.clear();
        EnemyInfoList.clear();
        anEntityTurn = false;
        isPassTurn = false;
        iCrit = false;
        input = false;
        whichScreen = NOTHING;
        escapeAnot = false;
        Overworld::battle = false;
        SceneManager::GetInstance()->PreviousScene();
        temp = 0.f;
    }
}

void BattleSystem::ChooseItems(BattleEntity* entity)
{
    if (KeyboardController::GetInstance()->IsKeyPressed(VK_UP))
        itemselect--;
    if (KeyboardController::GetInstance()->IsKeyPressed(VK_DOWN))
        itemselect++;

    if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
    {
        if (Player::GetInstance().GetInventory()->m_inventoryList.size() <= 0)
            noMoreItems = true;
        else
        {
            Player::GetInstance().GetInventory()->UseItem(itemselect, dynamic_cast<CharacterInfo*>(entity->GetInfo()));
            whichScreen = CHOOSEDOWAT;
            chooseItem = false;
        }
    }

    if (itemselect < 0)
        itemselect = Player::GetInstance().GetInventory()->m_inventoryList.size() - 1;
    if (itemselect > Player::GetInstance().GetInventory()->m_inventoryList.size() - 1)
        itemselect = 0;

    if (KeyboardController::GetInstance()->IsKeyPressed(VK_ESCAPE))
    {
        whichScreen = CHOOSEDOWAT;
        chooseItem = false;
    }

    if (KeyboardController::GetInstance()->IsKeyPressed(VK_RIGHT))
    {
        whichScreen = CHOOSEDOWAT;
        chooseItem = false;
    }
}

void BattleSystem::Exit()
{
    // Remove the meshes which are specific to CBattleState
    MeshBuilder::GetInstance()->RemoveMesh("BattleState_BKGROUND");
    MeshBuilder::GetInstance()->RemoveMesh("Commandselect");
    MeshBuilder::GetInstance()->RemoveMesh("enemysprite");

    delete Arrow;
    delete pewpewpew;
    delete CommandBox;
    // Detach camera from other entities
    GraphicsManager::GetInstance()->DetachCamera();
}