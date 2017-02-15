#include "BattleSystem.h"
#include "../Entity/EntityFactory.h"
#include "../Application.h"

#include "KeyboardController.h"

#include "RenderHelper.h"
#include "MeshBuilder.h"

/***************************************
///< Default constructor
A Default constructor for the Battle System, sets parameters here
*****************************************/
BattleSystem::BattleSystem() : 
anEntityTurn(false)
{
    float windowWidth = Application::GetInstance().GetWindowWidth();
    float windowHeight = Application::GetInstance().GetWindowHeight();

    CommandBox = EntityFactory::GetInstance()->CreateSprite("Commandselect", SpriteEntity::MODE_2D);
    CommandBox->SetPosition(Vector3(windowWidth * 0.85f, windowHeight * 0.3f, 1.f));
    CommandBox->SetScale(Vector3(windowWidth * 0.2, windowHeight * 0.4, 0.f));
}

/***************************************
///< destructor
A Default constructor for the Battle System, sets parameters here
*****************************************/
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

        //std::cout << (*itr)->GetATB() << std::endl;

        // Check if any entity is ready, if it is, stop the update of others.
        if ((*itr)->GetReady())
        {
            //std::cout << "Ur turn Yugi Boi" << std::endl;
            anEntityTurn = true;
            EntityTurn((*itr));
        }
    }

    //std::cout << "test" << std::endl;
}

// Returns a target player choosed
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

// This Entity can do whatever it's turn is.
void BattleSystem::EntityTurn(BattleEntity* entity)
{
    std::cout << "This Entity Turn!" << std::endl;

    if (KeyboardController::GetInstance()->IsKeyPressed(VK_F1))
    {
        BattleEntity* target = ChooseAtkTarget(entity);
        Attack(entity, target);
    }
    /*for (std::list<BattleEntity*>::iterator itr = BattleList.begin(); itr != BattleList.end(); itr++)
    {

    }*/
}

void BattleSystem::Attack(BattleEntity* entity, BattleEntity* targetEntity)
{
    InfoBase* myEntity = entity->GetInfo();
    InfoBase* targEntity = targetEntity->GetInfo();

    myEntity->stats.GetCritRate();
    if (targetEntity != nullptr)
    {
        std::cout << "Target Health: " << targetEntity->GetHP() << std::endl;
        std::cout << "Current Health: " << entity->GetHP() << std::endl;
        std::cout << targEntity->stats.GetDefence() << std::endl;

        int DamageDeal;

        if (iCrit)
        {
            DamageDeal = (myEntity->stats.GetDamage() * 1.5) - targEntity->stats.GetDefence();
            if (DamageDeal <= 0)
                DamageDeal = 0;
        }
        else
        {
            DamageDeal = myEntity->stats.GetDamage() - targEntity->stats.GetDefence();
            if (DamageDeal <= 0)
                DamageDeal = 0;
        }

        targetEntity->TakeDamage(DamageDeal);

        std::cout << "Dealt: " << DamageDeal << "to Target!" << std::endl;
        if (targetEntity->GetHP() <= 0)
        {
            std::cout << "Target Elimited!" << std::endl;
        }

        entity->SetATB(0.0);
        entity->SetReady(false);
        anEntityTurn = false;
    }
    else
        std::cout << "No More Target u dummy" << std::endl;
}

void BattleSystem::SpellCast(BattleEntity* entity, BattleEntity* targetEntity)
{
    InfoBase* myEntity = entity->GetInfo();
    InfoBase* targEntity = targetEntity->GetInfo();

    std::cout << "Casted Spell on Target!" << std::endl;
    //targEntity->HP - myEntity->stats.GetDamage();
}

void BattleSystem::Defend(BattleEntity* entity)
{
    InfoBase* myEntity = entity->GetInfo();
    myEntity->stats.GetDefence();
    std::cout << "You Defended!" << std::endl;
}
void BattleSystem::PassTurn(BattleEntity* entity)
{
    InfoBase* myEntity = entity->GetInfo();
    
    std::cout << "Passed a turn, gain an Attack Point!" << std::endl;
    // Add Turn Point
}

void BattleSystem::Render()
{
    if (anEntityTurn == true)
    {
        CommandBox->RenderUI();
    }
}