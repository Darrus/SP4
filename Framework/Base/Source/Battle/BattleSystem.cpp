#include "BattleSystem.h"
#include "../Entity/EntityFactory.h"
#include "../Application.h"

#include "KeyboardController.h"

#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "GraphicsManager.h"

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
attkselect(3),
whichScreen(NOTHING)
{
    float windowWidth = Application::GetInstance().GetWindowWidth();
    float windowHeight = Application::GetInstance().GetWindowHeight();

    MeshBuilder::GetInstance()->GenerateCube("HealthBar", Color(0, 1, 0), 1.f);
    MeshBuilder::GetInstance()->GenerateCube("RedBar", Color(1, 0, 0), 1.f);

    CommandBox = EntityFactory::GetInstance()->CreateSprite("Commandselect", SpriteEntity::MODE_2D);
    CommandBox->SetPosition(Vector3(windowWidth * 0.85f, windowHeight * 0.3f, 10.f));
    CommandBox->SetScale(Vector3(windowWidth * 0.2, windowHeight * 0.4, 0.f));

    Arrow = EntityFactory::GetInstance()->CreateSprite("RedBar", SpriteEntity::MODE_2D);
    Arrow->SetPosition(Vector3(windowWidth * 0.85f, windowHeight * 0.3f, 10.f));
    Arrow->SetScale(Vector3(windowWidth * 0.1, windowHeight * 0.01, 0.f));

    // Enemy Battle Sprites
    BattleSprites = EntityFactory::GetInstance()->CreateSprite("enemysprite", SpriteEntity::MODE_2D);
    BattleSprites->SetPosition(Vector3(windowWidth * 0.25f, windowHeight * 0.5f, 1.f));
    BattleSprites->SetScale(Vector3(windowWidth * 0.2, windowHeight * 0.2, 0.f));
    SpriteList.push_back(BattleSprites);
    BattleSprites = nullptr;

    BattleSprites = EntityFactory::GetInstance()->CreateSprite("enemysprite", SpriteEntity::MODE_2D);
    BattleSprites->SetPosition(Vector3(windowWidth * 0.25f, windowHeight * 0.25f, 1.f));
    BattleSprites->SetScale(Vector3(windowWidth * 0.2, windowHeight * 0.2, 0.f));
    SpriteList.push_back(BattleSprites);
    BattleSprites = nullptr;

    // Player Battle Sprites
    //SetPosition((Vector3(windowWidth * 0.75f, windowHeight * (0.1f * (i + 1.5)), 1.f)));
    BattleSprites = EntityFactory::GetInstance()->CreateSprite("player1", SpriteEntity::MODE_2D);
    BattleSprites->SetPosition(Vector3(windowWidth * 0.75f, windowHeight * 0.25f, 1.f));
    BattleSprites->SetScale(Vector3(windowWidth * 0.1, windowHeight * 0.1, 0.f));
    SpriteList.push_back(BattleSprites);
    BattleSprites = nullptr;

    BattleSprites = EntityFactory::GetInstance()->CreateSprite("player2", SpriteEntity::MODE_2D);
    BattleSprites->SetPosition(Vector3(windowWidth * 0.75f, windowHeight * 0.4f, 1.f));
    BattleSprites->SetScale(Vector3(windowWidth * 0.1, windowHeight * 0.1, 0.f));
    SpriteList.push_back(BattleSprites);
    BattleSprites = nullptr;

    BattleSprites = EntityFactory::GetInstance()->CreateSprite("player3", SpriteEntity::MODE_2D);
    BattleSprites->SetPosition(Vector3(windowWidth * 0.75f, windowHeight * 0.55f, 1.f));
    BattleSprites->SetScale(Vector3(windowWidth * 0.1, windowHeight * 0.1, 0.f));
    SpriteList.push_back(BattleSprites);
    BattleSprites = nullptr;

    for (int i = 0; i < 5; i++)
    {
        selection[i] = i;
    }
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
    // Loops through the entire EnemyList and do stuff
    for (std::list<BattleEntity*>::iterator itr = EnemyList.begin(); itr != EnemyList.end(); itr++)
    {
        if (!(*itr)->GetReady())
            (*itr)->Update(); ///< Updates the enemy ATB;
        else
        {
            std::cout << (*itr)->GetInfo()->name << " Launched an Attack!" << std::endl;
            BattleEntity* test = FindTarget(Math::RandIntMinMax(0, 2));

            if (test != nullptr)
                Attack((*itr), test);
            //ResetATB((*itr)); // Temp to reset the thing
            // perform the A.I. Attacks
        }
    }

    // Loops through the entire PlayerList and do stuff
    for (std::list<BattleEntity*>::iterator itr = PlayerList.begin(); itr != PlayerList.end(); itr++)
    {
        if (!(*itr)->GetReady())
            (*itr)->Update(); ///< Updates the player ATB;
        else
        {
            //std::cout << (*itr)->GetInfo()->name << " Launched an Attack!" << std::endl;
            //BattleEntity* test = ChooseAtkTarget(Math::RandIntMinMax(3, 4));
            //if (!(test)->GetDead())
            //    Attack((*itr), ChooseAtkTarget(Math::RandIntMinMax(3, 4)));

            if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE) && FindTarget(playerselect)->GetReady() && !anEntityTurn)
            {
                whichScreen = CHOOSEPLAYER;
            }
           
            if (playerselect > 2)
                playerselect = 0;
            if (playerselect < 0)
                playerselect = 2;
           
            GetInputSelection(FindTarget(playerselect), whichScreen, playerselect);
        }
    }
    if (whichScreen != CHOOSEPLAYER)
    {
        if (KeyboardController::GetInstance()->IsKeyPressed(VK_DOWN))
        {
            playerselect--;
        }
        if (KeyboardController::GetInstance()->IsKeyPressed(VK_UP))
        {
            playerselect++;
        }
    }
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
        if ((*itr)->GetHP() > 0 && (*itr)->GetInfo()->id == selection)
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
        if ((*itr)->GetHP() > 0 && (*itr)->GetInfo()->id == selection)
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
        if (KeyboardController::GetInstance()->IsKeyPressed(VK_F1))
        {
            whichScreen = CHOOSETARGET;
        }
        if (KeyboardController::GetInstance()->IsKeyPressed(VK_F2))
        {
            Defend(entity);
        }
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

            std::cout << "Dealt " << DamageDeal << " to " << targEntity->name << std::endl;
        }
        else
        {
            DamageDeal = 0;
            std::cout << targEntity->name << " has Dodged the Attack!" << std::endl;
        }

        if (targetEntity->GetHP() <= 0)
        {
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
    ResetATB(entity);
    isPassTurn = true;
    // Add Turn Point
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
    MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
    float windowWidth = Application::GetInstance().GetWindowWidth();
    float windowHeight = Application::GetInstance().GetWindowHeight();

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
    if (whichScreen == CHOOSETARGET)
    {
        if (attkselect == 3)
        {
            Arrow->SetPosition(Vector3(windowWidth * 0.25f, windowHeight * 0.5f, 10.f));
        }
        if (attkselect == 4)
        {
            Arrow->SetPosition(Vector3(windowWidth * 0.25f, windowHeight * 0.25f, 10.f));
        }
    }

    modelStack.PushMatrix();
    modelStack.Translate(windowWidth * 0.5, windowHeight * 0.1, 5.f);
    modelStack.Scale(windowWidth, windowHeight *0.2, 1.f);
    RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Commandselect"));
    modelStack.PopMatrix();

    for (std::list<BattleEntity*>::iterator it = PlayerList.begin(); it != PlayerList.end(); it++)
    {
        modelStack.PushMatrix();
        modelStack.Translate(windowWidth * 0.5, windowHeight * (0.05f * ((*it)->GetInfo()->id + 1)), 5.f);
        modelStack.Scale(20.f, 20.f, 1.f);
        RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*it)->GetInfo()->name + "   HP:   " + std::to_string((*it)->GetHP()), Color(0, 1, 0));
        modelStack.PopMatrix();
    }

    for (std::list<BattleEntity*>::iterator it = EnemyList.begin(); it != EnemyList.end(); it++)
    {
        modelStack.PushMatrix();
        modelStack.Translate(windowWidth * 0.05, windowHeight * (0.05f * ((*it)->GetInfo()->id - 2)), 5.f);
        modelStack.Scale(20.f, 20.f, 1.f);
        RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*it)->GetInfo()->name + "   HP:   " + std::to_string((*it)->GetHP()), Color(0, 1, 0));
        modelStack.PopMatrix();
    }

    for (std::list<BattleEntity*>::iterator it = BattleList.begin(); it != BattleList.end(); it++)
    {
        modelStack.PushMatrix();
        modelStack.Translate((*it)->GetPosition().x - 50.f, (*it)->GetPosition().y + 70.f, (*it)->GetPosition().z + 8);
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

    for (std::list<SpriteEntity*>::iterator itr = SpriteList.begin(); itr != SpriteList.end(); itr++)
    {
        (*itr)->RenderUI();
    }

    Arrow->RenderUI();
}

/***************************************
///< AssignPlayerParty
passes in the player party to be in the battlelist
*****************************************/
void BattleSystem::AssignPlayerParty(PartySystem* party)
{
    float windowWidth = Application::GetInstance().GetWindowWidth();
    float windowHeight = Application::GetInstance().GetWindowHeight();

    for (int i = 0; i < 3; i++)
    {
        CharacterInfo* pew = party->GetMember(i);
        pew->stats.UpdateStats();
        pewpewpew = new BattleEntity();
        pewpewpew->enemyType = BattleEntity::ALLY;
        pewpewpew->SetInfo(pew);

        if (pew != nullptr)
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
    }
    if (screen == CHOOSETARGET)
    {
        if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
        {
            Attack(entity, ChooseAtkTarget(attkselect));
        }

        if (KeyboardController::GetInstance()->IsKeyPressed(VK_DOWN))
        {
            attkselect--;
        }
        if (KeyboardController::GetInstance()->IsKeyPressed(VK_UP))
        {
            attkselect++;
        }

        if (attkselect > 4)
            attkselect = 3;
        if (attkselect < 3)
            attkselect = 4;
    }
}