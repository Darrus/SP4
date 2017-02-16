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
iDodge(false)
{
    float windowWidth = Application::GetInstance().GetWindowWidth();
    float windowHeight = Application::GetInstance().GetWindowHeight();

    MeshBuilder::GetInstance()->GenerateCube("HealthBar", Color(0, 1, 0), 1.f);
    MeshBuilder::GetInstance()->GenerateCube("RedBar", Color(1, 0, 0), 1.f);

    CommandBox = EntityFactory::GetInstance()->CreateSprite("Commandselect", SpriteEntity::MODE_2D);
    CommandBox->SetPosition(Vector3(windowWidth * 0.85f, windowHeight * 0.3f, 1.f));
    CommandBox->SetScale(Vector3(windowWidth * 0.2, windowHeight * 0.4, 0.f));

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

    //for (std::list<BattleEntity*>::iterator itr = BattleList.begin(); itr != BattleList.end(); itr++)
    //{

    //}

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
    // Loops through the Entire Battle entities to call their Updates;
    for (std::list<BattleEntity*>::iterator itr = BattleList.begin(); itr != BattleList.end(); itr++)
    {
        // Update Every Entity First to fill up their Attack Turn Bar
        if (!anEntityTurn)
            (*itr)->Update();

        //std::cout << (*itr)->GetATB() << std::endl;

        // Check if any entity is ready, if it is, stop the update of others.
        if ((*itr)->GetReady())
        {
            if (!anEntityTurn)
            {
                std::cout << (*itr)->GetInfo()->name << "'s Turn!" << std::endl;
                (*itr)->AddAttkTurnPt(1);
            }
            isPassTurn = false;
            anEntityTurn = true;
            EntityTurn((*itr));
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

    for (std::list<BattleEntity*>::iterator itr = BattleList.begin(); itr != BattleList.end(); itr++)
    {
        if ((*itr) != entity)
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
            BattleEntity* target = ChooseAtkTarget(entity);
            Attack(entity, target);
        }
        if (KeyboardController::GetInstance()->IsKeyPressed(VK_F2))
        {
            Defend(entity);
        }
        if (KeyboardController::GetInstance()->IsKeyPressed(VK_F3))
        {
            PassTurn(entity);
        }
    }

    /*for (std::list<BattleEntity*>::iterator itr = BattleList.begin(); itr != BattleList.end(); itr++)
    {

    }*/
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
}

/***************************************
///< Render
Renders All the current entities inside the Battle List.
*****************************************/
void BattleSystem::Render()
{
    for (std::list<BattleEntity*>::iterator it = BattleList.begin(); it != BattleList.end(); it++)
    {
        MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();

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
        modelStack.PushMatrix();
    }

    for (std::list<SpriteEntity*>::iterator itr = SpriteList.begin(); itr != SpriteList.end(); itr++)
    {
        (*itr)->RenderUI();
    }
    if (anEntityTurn == true)
    {
        CommandBox->RenderUI();
    }
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
        pewpewpew->SetInfo(pew);

        if (pew != nullptr)
        {
            pewpewpew->SetPosition((Vector3(windowWidth * 0.75f, windowHeight * (0.1f * (i + 1)), 1.f)));
            BattleList.push_back(pewpewpew);
        }
    }
}