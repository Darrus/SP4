#include "BattleSystem.h"
#include "../Entity/EntityFactory.h"
#include "../Application.h"

#include "KeyboardController.h"
#include "SceneManager.h"
#include "..\Battle\MonsterFactory.h"

#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "GraphicsManager.h"

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
attkselect(),
commandselect(0),
skillselect(0),
whichScreen(NOTHING),
addEXP(false),
turnPt(0),
chooseItem(false),
itemselect(0),
noMoreItems(false), 
choosingSkill(false)
{
    float windowWidth = Application::GetInstance().GetWindowWidth();
    float windowHeight = Application::GetInstance().GetWindowHeight();

    MeshBuilder::GetInstance()->GenerateCube("HealthBar", Color(0, 1, 0), 1.f);
    MeshBuilder::GetInstance()->GenerateCube("RedBar", Color(1, 0, 0), 1.f);

    CommandBox = new SpriteEntity(MeshBuilder::GetInstance()->GetMesh("Commandselect"));
    CommandBox->SetTextRenderMode(SpriteEntity::MODE_2D);
    CommandBox->SetPosition(Vector3(windowWidth * 0.85f, windowHeight * 0.3f, 10.f));
    CommandBox->SetScale(Vector3(windowWidth * 0.2, windowHeight * 0.4, 0.f));

    Arrow = new SpriteEntity(MeshBuilder::GetInstance()->GetMesh("arrow"));
    Arrow->SetTextRenderMode(SpriteEntity::MODE_2D);
    Arrow->SetPosition(Vector3(windowWidth * 0.85f, windowHeight * 0.3f, 10.f));
    Arrow->SetScale(Vector3(windowWidth * 0.05, windowHeight * 0.05, 0.f));

    // Enemy Battle Sprites
    BattleSprites = new SpriteEntity(MeshBuilder::GetInstance()->GetMesh("enemysprite"));
    BattleSprites->SetTextRenderMode(SpriteEntity::MODE_2D);
    BattleSprites->SetPosition(Vector3(windowWidth * 0.25f, windowHeight * 0.5f, 1.f));
    BattleSprites->SetScale(Vector3(windowWidth * 0.2, windowHeight * 0.2, 0.f));
    SpriteList.push_back(BattleSprites);
    BattleSprites = nullptr;

    BattleSprites = new SpriteEntity(MeshBuilder::GetInstance()->GetMesh("enemysprite"));
    BattleSprites->SetTextRenderMode(SpriteEntity::MODE_2D);
    BattleSprites->SetPosition(Vector3(windowWidth * 0.25f, windowHeight * 0.3f, 1.f));
    BattleSprites->SetScale(Vector3(windowWidth * 0.2, windowHeight * 0.2, 0.f));
    SpriteList.push_back(BattleSprites);
    BattleSprites = nullptr;

    // Player Battle Sprites
    //SetPosition((Vector3(windowWidth * 0.75f, windowHeight * (0.1f * (i + 1.5)), 1.f)));
    BattleSprites = new SpriteEntity(MeshBuilder::GetInstance()->GetMesh("player1"));
    BattleSprites->SetTextRenderMode(SpriteEntity::MODE_2D);
    BattleSprites->SetPosition(Vector3(windowWidth * 0.75f, windowHeight * 0.25f, 1.f));
    BattleSprites->SetScale(Vector3(windowWidth * 0.1, windowHeight * 0.1, 0.f));
    SpriteList.push_back(BattleSprites);
    BattleSprites = nullptr;

    BattleSprites = new SpriteEntity(MeshBuilder::GetInstance()->GetMesh("player2"));
    BattleSprites->SetTextRenderMode(SpriteEntity::MODE_2D);
    BattleSprites->SetPosition(Vector3(windowWidth * 0.75f, windowHeight * 0.4f, 1.f));
    BattleSprites->SetScale(Vector3(windowWidth * 0.1, windowHeight * 0.1, 0.f));
    SpriteList.push_back(BattleSprites);
    BattleSprites = nullptr;

    BattleSprites = new SpriteEntity(MeshBuilder::GetInstance()->GetMesh("player3"));
    BattleSprites->SetTextRenderMode(SpriteEntity::MODE_2D);
    BattleSprites->SetPosition(Vector3(windowWidth * 0.75f, windowHeight * 0.55f, 1.f));
    BattleSprites->SetScale(Vector3(windowWidth * 0.1, windowHeight * 0.1, 0.f));
    SpriteList.push_back(BattleSprites);
    BattleSprites = nullptr;

    for (int i = 0; i < 5; i++)
    {
        selection[i] = i;
    }

    enemyAI = new EnemyAI();
    //enemyAI->battlelog = new BattleLog();
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
    //if (!battlelog->Update())
    enemyAI->battlelog->Update();
    // Loops through the entire EnemyList and do stuff
    for (std::list<BattleEntity*>::iterator itr = EnemyList.begin(); itr != EnemyList.end(); itr++)
    {
        if (!(*itr)->GetReady())
            (*itr)->Update(); ///< Updates the enemy ATB;
        else
        {
            std::cout << (*itr)->GetInfo()->name << " Launched an Attack!" << std::endl;
            BattleEntity* test = FindTarget(Math::RandIntMinMax(0, 2));

            enemyAI->aggroLvl = EnemyAI::HIGH;

            if (test != nullptr)
                enemyAI->DetermineAction((*itr), test);
        }
    }

    // Loops through the entire PlayerList and do stuff
    for (std::list<BattleEntity*>::iterator itr = PlayerList.begin(); itr != PlayerList.end(); itr++)
    {
        if (CheckAnyAlive() == nullptr)
            CheckBattleEnd((*itr));
        else
        {
            if (!(*itr)->GetReady())
                (*itr)->Update(); ///< Updates the player ATB;
            else
                ChoosePlayerInput();
        }
    }

    //if (whichScreen != CHOOSEPLAYER && whichScreen != CHOOSETARGET && whichScreen != CHOOSEDOWAT && whichScreen != CHOOSESKILL && whichScreen != CHOOSEITEM)
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

        if (playerselect > (Player::GetInstance().GetParty()->memberCount() - 2))
            playerselect = 0;
        if (playerselect < 0)
            playerselect = (Player::GetInstance().GetParty()->memberCount() - 2);
    }


    if (commandselect < 0)
        commandselect = 4;
    if (commandselect >= 5)
        commandselect = 0;

    if (playerselect > (Player::GetInstance().GetParty()->memberCount() - 2))
        playerselect = 0;
    if (playerselect < 0)
        playerselect = (Player::GetInstance().GetParty()->memberCount() - 2);

    if (skillselect < 0)
        skillselect = 4;
    if (skillselect >= 5)
        skillselect = 0;


    if (attkselect >((Player::GetInstance().GetParty()->memberCount() - 1) + (EnemyList.size() - 1)))
        attkselect = (Player::GetInstance().GetParty()->memberCount() - 1);
    if (attkselect < (Player::GetInstance().GetParty()->memberCount() - 1))
        attkselect = ((Player::GetInstance().GetParty()->memberCount() - 1) + (EnemyList.size() - 1));

}

void BattleSystem::CheckBattleEnd(BattleEntity* entity)
{
    if (!addEXP)
    {
        for (int i = 0; i < (Player::GetInstance().GetParty()->memberCount() - 1); i++)
        {
            Player::GetInstance().GetParty()->GetMember(i)->EXP += 99999;
            if (Player::GetInstance().GetParty()->GetMember(i)->stats.Getlevel() < 100)
                Player::GetInstance().GetParty()->GetMember(i)->stats.AddLevel(Player::GetInstance().GetParty()->GetMember(i)->CheckLevelUp());

            Player::GetInstance().GetParty()->GetMember(i)->HP = Player::GetInstance().GetParty()->GetMember(i)->stats.GetMaxHP();
            Player::GetInstance().GetParty()->GetMember(i)->MP = Player::GetInstance().GetParty()->GetMember(i)->stats.GetMaxMP();
        }
        addEXP = true;
    }
    if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
    {
        Overworld::battle = false;
        addEXP = false;
        Player::GetInstance().DoDie();

        SceneManager::GetInstance()->PreviousScene();
        anEntityTurn = false;
        isPassTurn = false;
        iCrit = false;
        whichScreen = NOTHING;
        enemyAI->battlelog->battleloglist.clear();
    }
}

void BattleSystem::ChoosePlayerInput()
{
    if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE) && FindTarget(playerselect)->GetReady() && !anEntityTurn && whichScreen == NOTHING && !FindTarget(playerselect)->GetDead())
    {
        whichScreen = CHOOSEPLAYER;
    }

    if (playerselect > (Player::GetInstance().GetParty()->memberCount() - 2))
        playerselect = 0;
    if (playerselect < 0)
        playerselect = (Player::GetInstance().GetParty()->memberCount() - 2);

    GetInputSelection(FindTarget(playerselect), whichScreen, playerselect);
}

/***************************************
///< ChooseAtkTarget
    Chooses a Target to return to the player
///< param entity
    Passes in the entity to cross-check that it doesn't return itself and attack itself

///< returns (*itr)
    Returns an Entity for the target to attack.
*****************************************/
BattleEntity* BattleSystem::ChooseAtkTarget(BattleEntity* entity)
{
    for (std::list<BattleEntity*>::iterator itr = EnemyList.begin(); itr != EnemyList.end(); itr++)
    {
        if ((*itr) != entity && (*itr)->GetHP() > 0)
        {
            return (*itr);
        }
    }
    return nullptr;
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

BattleEntity* BattleSystem::FindTarget(int selection)
{
    for (std::list<BattleEntity*>::iterator itr = PlayerList.begin(); itr != PlayerList.end(); itr++)
    {
        if ((*itr)->GetInfo()->id == selection)
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
        std::cout << targEntity->name << "'s Health: " << targetEntity->GetHP() << std::endl;
        std::cout << myEntity->name <<  "'s Health : " << entity->GetHP() << std::endl;

        int DamageDeal;
        CheckCrit(myEntity->stats.GetCritRate());
        CheckDodge(targEntity->stats.GetDodgeRate());
        if (!iDodge)
        {
            if (iCrit)
            {
                std::cout << myEntity->name << " has Crited!" << std::endl;
                DamageDeal = (myEntity->stats.GetDamage() * 1.5) - (targEntity->stats.GetDefence() * targetEntity->GetDefending());
                if (DamageDeal <= 0)
                    DamageDeal = 0;
            }
            else
            {
                DamageDeal = myEntity->stats.GetDamage() - (targEntity->stats.GetDefence() * targetEntity->GetDefending());
                if (DamageDeal <= 0)
                    DamageDeal = 0;
            }
            targetEntity->TakeDamage(DamageDeal);
            enemyAI->battlelog = new BattleLog(targetEntity, myEntity->name, DamageDeal, DamageDeal, iDodge, iCrit);
            enemyAI->battlelog->battleloglist.push_back(enemyAI->battlelog);
            std::cout << "Dealt " << DamageDeal << " to " << targEntity->name << std::endl;
        }
        else
        {
            DamageDeal = 0;
            std::cout << targEntity->name << " has Dodged the Attack!" << std::endl;
        }

        if (targetEntity->GetHP() <= 0)
        {
            targetEntity->GetInfo()->HP = 0;
            std::cout << targEntity->name << " Elimited!" << std::endl;
            battleEnded = true;
        }

        entity->SetDefending(1);
        entity->DecreaseAttkTurnPt(1);

        if (entity->GetAttkTurnPt() > 0)
            std::cout << "You gain another turn!" << std::endl << std::endl;
        else
            ResetATB(entity);
    }
    else
        std::cout << "No More Target u dummy" << std::endl;
}

/***************************************
///< SpellCast
Entity Attacks another Entity, and do following calculations

///< param entity
The entity that unleashes the Spell

///< param targetEntity
Target Entity which the Entity chosed to cast spell on.
*****************************************/
void BattleSystem::SpellCast(BattleEntity* entity, BattleEntity* targetEntity)
{
    InfoBase* myEntity = entity->GetInfo();
    InfoBase* targEntity = targetEntity->GetInfo();

    std::cout << "Casted Spell on Target!" << std::endl;
    entity->DecreaseAttkTurnPt(1);
    //targEntity->HP - myEntity->stats.GetDamage();

    if (entity->GetAttkTurnPt() > 0)
        std::cout << "You gain another turn!" << std::endl << std::endl;
    else
        ResetATB(entity);
}

/***************************************
///< CheckCrit
Determine if Entity Crits

///< param critRate
passes in Crit Rate of Entity
*****************************************/
void BattleSystem::CheckCrit(float critRate)
{
    if (critRate >= (Math::RandFloatMinMax(0, 100)))
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
    if (dodgeRate >= (Math::RandFloatMinMax(0, 100)))
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
    std::cout << "You Defended!" << std::endl;
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
    std::cout << "Passed a turn, gain an Attack Point!" << std::endl;
    if (entity->GetAttkTurnPt() >= 5)
        entity->DecreaseAttkTurnPt(1);
    ResetATB(entity);
    isPassTurn = true;
}

/***************************************
///< Flee Battle
Allows the Player to flee the battle
*****************************************/
void BattleSystem::FleeBattle()
{
    std::cout << "Fled the Battle" << std::endl;
    Overworld::battle = false;
    SceneManager::GetInstance()->PreviousScene();
}

/***************************************
///< ResetATB
Whenever a unit casts finished a command, the Attack Bar will reset, will only cast if it has no more Turn Point or it Defended.
///< param entity
The entity that has used up all turn point or defended.
*****************************************/
void BattleSystem::ResetATB(BattleEntity* entity)
{
    std::cout << "Turn ended" << std::endl << std::endl;
    entity->SetATB(0.0);
    entity->SetReady(false);
    anEntityTurn = false;
    isPassTurn = false;
    iCrit = false;
    whichScreen = NOTHING;
}

/***************************************
///< Render
Renders All the current entities inside the Battle List.
*****************************************/
void BattleSystem::Render()
{
    if (CheckAnyAlive() == nullptr)
        ShowBattleResults();
    else
    {
        if (Overworld::battle != false)
        {
            RenderUIStuff();
            RenderEntities();
            //battlelog->Render();
            enemyAI->battlelog->Render();
            if (chooseItem == true)
                RenderInventory();
            if (noMoreItems == true)
                NoMoreItems();
        }
    }
}

void BattleSystem::NoMoreItems()
{
    MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
    float windowWidth = Application::GetInstance().GetWindowWidth();
    float windowHeight = Application::GetInstance().GetWindowHeight();
    float dt = (double)StopWatch::GetInstance()->GetDeltaTime();
    float pew = 0;

    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * 0.35, windowHeight * 0.7, 5.f);
    modelStack.Scale(30, 30, 1.f);
    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "NO MORE ITEMS", Color(0, 1, 0));
    modelStack.PopMatrix();

    pew += dt;
    if (pew > 3.f)
    {
        pew = 0.f;
        noMoreItems = false;
    }
}

void BattleSystem::RenderUIStuff()
{
    float TEXTSCALE = 35.f;
    MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
    float windowWidth = Application::GetInstance().GetWindowWidth();
    float windowHeight = Application::GetInstance().GetWindowHeight();
        if (whichScreen == NOTHING)
        {
            if (playerselect == 0)
            {
                Arrow->SetPosition(Vector3(windowWidth * 0.8f, windowHeight * 0.25f, 10.f));
            }
            if (playerselect == 1)
            {
                Arrow->SetPosition(Vector3(windowWidth * 0.8f, windowHeight * 0.4f, 10.f));
            }
            if (playerselect == 2)
            {
                Arrow->SetPosition(Vector3(windowWidth * 0.8f, windowHeight * 0.55f, 10.f));
            }
            if (playerselect == 3)
            {
                Arrow->SetPosition(Vector3(windowWidth * 0.8f, windowHeight * 0.7f, 10.f));
            }
        }
        if (whichScreen == CHOOSETARGET)
        {
            if (attkselect == 3)
            {
                Arrow->SetPosition(Vector3(windowWidth * 0.35f, windowHeight * 0.25f, 10.f));
            }
            if (attkselect == 4)
            {
                Arrow->SetPosition(Vector3(windowWidth * 0.35f, windowHeight * 0.4f, 10.f));
            }
            if (attkselect == 5)
            {
                Arrow->SetPosition(Vector3(windowWidth * 0.35f, windowHeight * 0.55f, 10.f));
            }
            if (attkselect == 6)
            {
                Arrow->SetPosition(Vector3(windowWidth * 0.35f, windowHeight * 0.7f, 10.f));
            }
        }
        if (whichScreen == CHOOSEDOWAT)
        {
            float DIST = 0.95;
            if (commandselect == 0)
                Arrow->SetPosition(Vector3(windowWidth * DIST, windowHeight * 0.65, 10.f));
            if (commandselect == 1)
                Arrow->SetPosition(Vector3(windowWidth * DIST, windowHeight * 0.6, 10.f));
            if (commandselect == 2)
                Arrow->SetPosition(Vector3(windowWidth * DIST, windowHeight * 0.55, 10.f));
            if (commandselect == 3)
                Arrow->SetPosition(Vector3(windowWidth * DIST, windowHeight * 0.5, 10.f));
            if (commandselect == 4)
                Arrow->SetPosition(Vector3(windowWidth * DIST, windowHeight * 0.45, 10.f));
        }
        if (whichScreen == CHOOSESKILL)
        {
            int i = 0;
            for (auto itritr = Player::GetInstance().GetParty()->GetMember(playerselect)->skills.begin(); itritr != Player::GetInstance().GetParty()->GetMember(playerselect)->skills.end(); ++itritr)
            {
                modelStack.PushMatrix();
                modelStack.Translate(windowWidth * 0.5f, windowHeight *  (0.7f + (i * -0.05f)), 5.f);
                modelStack.Scale(30.f, 30.f, 1.f);
                RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*itritr)->GetName(), Color(0, 1, 0));
                modelStack.PopMatrix();
                ++i;
            }
        }
        if (anEntityTurn)
        {
            float FIRSTONE = 0.65;
            modelStack.PushMatrix();
            modelStack.Translate(windowWidth * 0.9, windowHeight * 0.55, 5.f);
            modelStack.Scale(windowWidth *0.15, windowHeight *0.4, 1.f);
            RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Commandselect"));
            modelStack.PopMatrix();

            modelStack.PushMatrix();
            modelStack.Translate(windowWidth * 0.85, windowHeight * 0.7, 5.f);
            modelStack.Scale(TEXTSCALE, TEXTSCALE, 1.f);
            RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Turn Pt: " + std::to_string(turnPt), Color(0, 1, 0));
            modelStack.PopMatrix();

            modelStack.PushMatrix();
            modelStack.Translate(windowWidth * 0.85, windowHeight * FIRSTONE, 5.f);
            modelStack.Scale(TEXTSCALE, TEXTSCALE, 1.f);
            RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Attack", Color(0, 1, 0));
            modelStack.PopMatrix();

            modelStack.PushMatrix();
            modelStack.Translate(windowWidth * 0.85, windowHeight * (FIRSTONE - 0.05), 5.f);
            modelStack.Scale(TEXTSCALE, TEXTSCALE, 1.f);
            RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Defend", Color(0, 1, 0));
            modelStack.PopMatrix();

            modelStack.PushMatrix();
            modelStack.Translate(windowWidth * 0.85, windowHeight * (FIRSTONE - 0.1), 5.f);
            modelStack.Scale(TEXTSCALE, TEXTSCALE, 1.f);
            RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Skills", Color(0, 1, 0));
            modelStack.PopMatrix();

            modelStack.PushMatrix();
            modelStack.Translate(windowWidth * 0.85, windowHeight * (FIRSTONE - 0.15), 5.f);
            modelStack.Scale(TEXTSCALE, TEXTSCALE, 1.f);
            RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Item", Color(0, 1, 0));
            modelStack.PopMatrix();

            modelStack.PushMatrix();
            modelStack.Translate(windowWidth * 0.85, windowHeight * (FIRSTONE - 0.2), 5.f);
            modelStack.Scale(TEXTSCALE, TEXTSCALE, 1.f);
            RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Flee", Color(0, 1, 0));
            modelStack.PopMatrix();
        }
    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * 0.5, windowHeight * 0.1, 5.f);
    modelStack.Scale(windowWidth, windowHeight *0.2, 1.f);
    RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Commandselect"));
    modelStack.PopMatrix();

    Arrow->RenderUI();
}

void BattleSystem::RenderEntities()
{
    MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
    float windowWidth = Application::GetInstance().GetWindowWidth();
    float windowHeight = Application::GetInstance().GetWindowHeight();

    //for (std::list<BattleEntity*>::iterator it = PlayerList.begin(); it != PlayerList.end(); it++)
    //{
    //    modelStack.PushMatrix();
    //    modelStack.Translate(windowWidth * 0.5, windowHeight * (0.05f * ((*it)->GetInfo()->id + 1)), 5.f);
    //    modelStack.Scale(35.f, 35.f, 1.f);
    //    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*it)->GetInfo()->name + "   HP:   " + std::to_string((*it)->GetHP()), Color(0, 1, 0));
    //    modelStack.PopMatrix();
    //}
    for (int i = 0; i < (Player::GetInstance().GetParty()->memberCount() - 1); i++)
    {
        modelStack.PushMatrix();
        modelStack.Translate(windowWidth * 0.5, windowHeight * (0.05f * (Player::GetInstance().GetParty()->GetMember(i)->id + 1)), 5.f);
        modelStack.Scale(35.f, 35.f, 1.f);
        RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), Player::GetInstance().GetParty()->GetMember(i)->name + "   HP:   " + std::to_string(Player::GetInstance().GetParty()->GetMember(i)->HP), Color(0, 1, 0));
        modelStack.PopMatrix();
    }

    for (std::list<BattleEntity*>::iterator it = EnemyList.begin(); it != EnemyList.end(); it++)
    {
        modelStack.PushMatrix();
        modelStack.Translate(windowWidth * 0.05, windowHeight * (0.05f * ((*it)->GetInfo()->id - 2)), 5.f);
        modelStack.Scale(35.f, 35.f, 1.f);
        RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*it)->GetInfo()->name + "   HP:   " + std::to_string((*it)->GetHP()), Color(0, 1, 0));
        modelStack.PopMatrix();
    }

    for (std::list<BattleEntity*>::iterator it = BattleList.begin(); it != BattleList.end(); it++)
    {
        if (!(*it)->GetDead())
        {
            modelStack.PushMatrix();
            modelStack.Translate((*it)->GetPosition().x - 50.f, (*it)->GetPosition().y + 70.f, (*it)->GetPosition().z + 4);
            modelStack.Scale(25.f, 25.f, 1.f);
            RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*it)->GetInfo()->name, Color(0, 1, 0));
            modelStack.PopMatrix();

            modelStack.PushMatrix();
            modelStack.Translate((*it)->GetPosition().x, (*it)->GetPosition().y + 60.f, (*it)->GetPosition().z + 5);
            modelStack.Scale(100.f, 6.f, 1.f);
            RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("RedBar"));
            modelStack.PopMatrix();

            modelStack.PushMatrix();
            modelStack.Translate((*it)->GetPosition().x - Math::Max(0.f, (1 - (*it)->GetATB() / 100.f)) * 50.f, (*it)->GetPosition().y + 60.f, (*it)->GetPosition().z + 6);
            modelStack.Scale((Math::Max(0.f, (*it)->GetATB() / 100.f)) * 100.f, 6.f, 1.f);
            RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("HealthBar"));
            modelStack.PopMatrix();
        }
    }
    for (std::list<SpriteEntity*>::iterator itr = SpriteList.begin(); itr != SpriteList.end(); itr++)
    {
        (*itr)->RenderUI();
    }
}

void BattleSystem::RenderInventory()
{
    float windowWidth = Application::GetInstance().GetWindowWidth();
    float windowHeight = Application::GetInstance().GetWindowHeight();
    MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();

    Inventory* pewinventory = Player::GetInstance().GetInventory();
    
    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * 0.65, windowHeight * 0.5, 9.f);
    modelStack.Scale(windowWidth *0.3, windowHeight *0.5, 1.f);
    RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Commandselect"));
    modelStack.PopMatrix();

    for (unsigned i = 0; i < pewinventory->m_inventoryList.size(); ++i)
    {
        float FIRSTONE = 0.65;
        modelStack.PushMatrix();
        modelStack.Translate(windowWidth * 0.5, windowHeight * (0.7f + (i * -0.05f)), 9.f);
        modelStack.Scale(35.f, 35.f, 1.f);
        RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), std::to_string(i + 1) + ": "+ pewinventory->m_inventoryList[i]->GetName(), Color(0, 1, 0));
        modelStack.PopMatrix();
        //std::cout << i + 1 << ": " << pewinventory->m_inventoryList[i]->GetName() << " -> " << pewinventory->m_inventoryList[i]->GetDescription() << std::endl;
        //Player::GetInstance().GetInventory()->RenderItem(1, windowWidth * 0.5, windowHeight * 0.5 , 5, 5);
    }

    if (whichScreen == CHOOSEITEM)
    {
        float DIST = 0.75;
        if (itemselect == 0)
            Arrow->SetPosition(Vector3(windowWidth * DIST, windowHeight * 0.7, 10.f));
        if (itemselect == 1)
            Arrow->SetPosition(Vector3(windowWidth * DIST, windowHeight * 0.65, 10.f));
        if (itemselect == 2)
            Arrow->SetPosition(Vector3(windowWidth * DIST, windowHeight * 0.6, 10.f));
        if (itemselect == 3)
            Arrow->SetPosition(Vector3(windowWidth * DIST, windowHeight * 0.55, 10.f));
        if (itemselect == 4)
            Arrow->SetPosition(Vector3(windowWidth * DIST, windowHeight * 0.5, 10.f));
    }
}

void BattleSystem::ShowBattleResults()
{
    MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
    float windowWidth = Application::GetInstance().GetWindowWidth();
    float windowHeight = Application::GetInstance().GetWindowHeight();

    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * 0.5, windowHeight * 0.5, 8.5f);
    modelStack.Scale(windowWidth *0.8, windowHeight * 0.8, 1.f);
    RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Commandselect"));
    modelStack.PopMatrix();
    
    int expgain = 999;
    PartySystem* pew = Player::GetInstance().GetParty();
    for (auto it = PlayerInfoList.begin(); it != PlayerInfoList.end(); it++)
    {
        for (int i = 0; i < (Player::GetInstance().GetParty()->memberCount() - 1); ++i)
        {
            //std::cout << pew->GetMember(i)->CheckLevelUp() << std::endl;
            std::cout << pew->GetMember(i)->name << std::endl;
            
            //std::cout << pew->GetMember(i)->EXP << std::endl;
            modelStack.PushMatrix();
            modelStack.Translate(windowWidth * 0.2, windowHeight * (0.8f + (i * -0.05)), 9.f);
            modelStack.Scale(20.f, 20.f, 1.f);
            if ((*it)->id == i)
                RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), Player::GetInstance().GetParty()->GetMember(i)->name + " has Earned: " + std::to_string(expgain) + " Experience Pts!  Lvl: " + std::to_string(Player::GetInstance().GetParty()->GetMember(i)->stats.Getlevel()), Color(0, 1, 0));
            modelStack.PopMatrix();
        }
    }

    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * 0.2, windowHeight * 0.2f, 9.f);
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
    float windowWidth = Application::GetInstance().GetWindowWidth();
    float windowHeight = Application::GetInstance().GetWindowHeight();

    Player::GetInstance().GetParty();
    for (int i = 0; i < (Player::GetInstance().GetParty()->memberCount() - 1); ++i)
    {
        CharacterInfo* MemberInfo = Player::GetInstance().GetParty()->GetMember(i);
        Player::GetInstance().GetParty()->GetMember(i)->stats.UpdateStats();
        PlayerInfoList.push_back(Player::GetInstance().GetParty()->GetMember(i));
        pewpewpew = new BattleEntity();
        pewpewpew->enemyType = BattleEntity::ALLY;
        pewpewpew->SetInfo((Player::GetInstance().GetParty()->GetMember(i)));
        if (Player::GetInstance().GetParty()->GetMember(i) != nullptr)
        {
            pewpewpew->SetPosition((Vector3(windowWidth * 0.75f, windowHeight * (0.15f * (i + 1.5)), 1.f)));
            BattleList.push_back(pewpewpew);
            PlayerList.push_back(pewpewpew);
        }
    }
}

void BattleSystem::GetInputSelection(BattleEntity* entity, SELECTIONAT screen, int selection)
{
    if (screen == CHOOSEPLAYER)
    {
        if (!anEntityTurn)
        {
            std::cout << entity->GetInfo()->name << "'s Turn!" << std::endl;
            entity->AddAttkTurnPt(1);
        }
        isPassTurn = false;
        anEntityTurn = true;
        EntityTurn(entity);

        if (KeyboardController::GetInstance()->IsKeyReleased(VK_ESCAPE))
        {
            anEntityTurn = false;
            //anEntityTurn = false;
            whichScreen = NOTHING;
        }
    }
    if (screen == CHOOSETARGET)
    {
        turnPt = entity->GetAttkTurnPt();
        if (KeyboardController::GetInstance()->IsKeyReleased(VK_SPACE))
        {
            if (!ChooseAtkTarget(attkselect)->GetDead())
                Attack(entity, ChooseAtkTarget(attkselect));
            else
                std::cout << "Target is ded" << std::endl;
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

        if (attkselect > ((Player::GetInstance().GetParty()->memberCount() - 1) + (EnemyList.size() - 1)))
            attkselect = (Player::GetInstance().GetParty()->memberCount() - 1);
        if (attkselect < (Player::GetInstance().GetParty()->memberCount() - 1))
            attkselect = ((Player::GetInstance().GetParty()->memberCount() - 1) + (EnemyList.size() - 1));
    }
    if (screen == CHOOSESKILL)
    {
        if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
        {
            choosingSkill = true;
        }

        if (KeyboardController::GetInstance()->IsKeyPressed(VK_DOWN))
            skillselect--;
        if (KeyboardController::GetInstance()->IsKeyPressed(VK_UP))
            skillselect++;

        if (KeyboardController::GetInstance()->IsKeyPressed(VK_ESCAPE))
        {
            anEntityTurn = false;
            whichScreen = NOTHING;
        }

        if (skillselect < 0)
            skillselect = (Player::GetInstance().GetParty()->GetMember(playerselect)->skills.size() - 1);
        if (skillselect >= (Player::GetInstance().GetParty()->GetMember(playerselect)->skills.size() - 1))
            skillselect = 0;

        if (choosingSkill == true)
            ChooseSkill();
    }

    if (screen == CHOOSEDOWAT)
    {
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
                FleeBattle();               // Flee
        }

        if (KeyboardController::GetInstance()->IsKeyPressed(VK_DOWN))
            commandselect++;
        if (KeyboardController::GetInstance()->IsKeyPressed(VK_UP))
            commandselect--;

        if (KeyboardController::GetInstance()->IsKeyPressed(VK_ESCAPE))
        {
            anEntityTurn = false;
            whichScreen = NOTHING;
        }
    }
    if (screen == CHOOSEITEM)
    {
        chooseItem = true;
        ChooseItems(entity);
    }
}

void BattleSystem::ChooseItems(BattleEntity* entity)
{
    //Player::GetInstance().GetInventory()->PrintInventory();

    Player::GetInstance().GetInventory()->m_inventoryList;

    if (KeyboardController::GetInstance()->IsKeyPressed(VK_UP))
        itemselect--;
    if (KeyboardController::GetInstance()->IsKeyPressed(VK_DOWN))
        itemselect++;

    if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
    {
        if (Player::GetInstance().GetInventory()->m_inventoryList.size() <= 0)
        {
            std::cout << "No Items to use" << std::endl;
            noMoreItems = true;
        }
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
}

void BattleSystem::ChooseSkill()
{
    int i = 0;
    for (auto itritr = Player::GetInstance().GetParty()->GetMember(playerselect)->skills.begin(); itritr != Player::GetInstance().GetParty()->GetMember(playerselect)->skills.end(); ++itritr)
    {
        if ((*itritr)->IsAllyTargetable())
        {
            SkillParameters foo;
            foo.caster = Player::GetInstance().GetParty()->GetMember(playerselect);
            for (int i = 0; i < (Player::GetInstance().GetParty()->memberCount() - 1); ++i)
            {
                if (Player::GetInstance().GetParty()->GetMember(i) != nullptr)
                    foo.targetList.push_back(Player::GetInstance().GetParty()->GetMember(i));
            }
            (*itritr)->UseSkill(foo);

            enemyAI->battlelog = new BattleLog(foo.caster, (*itritr)->GetName());
            enemyAI->battlelog->battleloglist.push_back(enemyAI->battlelog);
            choosingSkill = false;
        }
        else if ((*itritr)->IsEnemyTargetable())
        {
            //SkillParameters foo;
            //foo.caster = Player::GetInstance().GetParty()->GetMember(playerselect);

            //for (int i = 0; i < EnemyList.size(); ++i)
            //{
            //    if (Player::GetInstance().GetParty()->GetMember(i) != nullptr)
            //        foo.targetList.push_back(Player::GetInstance().GetParty()->GetMember(i));
            //}
            //(*itritr)->UseSkill(foo);
        }

        ++i;
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