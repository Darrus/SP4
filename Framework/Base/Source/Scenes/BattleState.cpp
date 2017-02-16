#include <iostream>
#include "BattleState.h"
#include "GL\glew.h"
#include "LoadTGA.h"

#include "../Application.h"
#include "GraphicsManager.h"
#include "MeshBuilder.h"
#include "RenderHelper.h"

#include "KeyboardController.h"
#include "SceneManager.h"

#include "../Lua/LuaInterface.h"
#include "SoundEngine\SoundEngine.h"

#include "../Entity/EntityFactory.h"

using namespace std;    

CBattleState::CBattleState() :
state(IDLE),
health_(100),
attack_(20),
defense_(5),
atkbar_(0),
fillrate(17),

state2(IDLE),
health2_(100),
attack2_(30),
defense2_(10),
atkbar2_(0),
fillrate2(20),

encounter(false)
{
}
CBattleState::~CBattleState()
{

}

void CBattleState::Init()
{
	// Create and attach the camera to the scene
	camera.Init(Vector3(0, 0, 0), Vector3(0, 0, -1), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	// Load all the meshes
	MeshBuilder::GetInstance()->GenerateQuad("BattleState_BKGROUND", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("BattleState_BKGROUND")->textureID = LoadTGA("Image//splash.tga");

    MeshBuilder::GetInstance()->GenerateQuad("Commandselect", Color(1, 1, 1), 1.f);
    MeshBuilder::GetInstance()->GetMesh("Commandselect")->textureID = LoadTGA("Image//optionbox.tga");

    MeshBuilder::GetInstance()->GenerateQuad("enemysprite", Color(1, 1, 1), 1.f);
    MeshBuilder::GetInstance()->GetMesh("enemysprite")->textureID = LoadTGA("Image//enemy.tga");

	MeshBuilder::GetInstance()->GenerateText("text", 16, 16);
	MeshBuilder::GetInstance()->GetMesh("text")->textureID = LoadTGA("Image//calibri.tga");
	MeshBuilder::GetInstance()->GetMesh("text")->material.kAmbient.Set(1, 0, 0);

	Lua->LoadFile("Sound");
	SoundEngine::GetInstance()->SetMasterVolume(CLuaInterface::GetInstance()->GetFloatValue("BGM_Volume"));
	SoundEngine::GetInstance()->AddRepeatSound("splash_bgm", "Sound/splash_bgm.mp3", 1.f);
	SoundEngine::GetInstance()->Play("splash_bgm");

	float windowWidth = Application::GetInstance().GetWindowWidth();
	float windowHeight = Application::GetInstance().GetWindowHeight();

	BattleStateBackground = EntityFactory::GetInstance()->CreateSprite("BattleState_BKGROUND", SpriteEntity::MODE_2D);
	BattleStateBackground->SetPosition(Vector3(windowWidth * 0.5f, windowHeight * 0.5f, 0.f));
	BattleStateBackground->SetScale(Vector3(windowWidth, windowHeight, 0.f));

    CommandBox = EntityFactory::GetInstance()->CreateSprite("Commandselect", SpriteEntity::MODE_2D);
    CommandBox->SetPosition(Vector3(windowWidth * 0.85f, windowHeight * 0.3f, 1.f));
    CommandBox->SetScale(Vector3(windowWidth * 0.2, windowHeight * 0.4, 0.f));

    position_.Set(windowWidth * 0.1, windowHeight * 0.8, 0);
    position2_.Set(windowWidth * 0.9, windowHeight * 0.8, 0);

    TestEnemy = EntityFactory::GetInstance()->CreateSprite("enemysprite", SpriteEntity::MODE_2D);
    TestEnemy->SetPosition(Vector3(position_.x, position_.y, 1.f));
    TestEnemy->SetScale(Vector3(windowWidth * 0.1, windowHeight * 0.1, 0.f));

    TestEnemy2 = EntityFactory::GetInstance()->CreateSprite("enemysprite", SpriteEntity::MODE_2D);
    TestEnemy2->SetPosition(Vector3(position2_.x, position2_.y, 1.f));
    TestEnemy2->SetScale(Vector3(windowWidth * 0.1, windowHeight * 0.1, 0.f));

	MeshBuilder::GetInstance()->GenerateSpriteAnimation("Character", 4, 9);
	MeshBuilder::GetInstance()->GetMesh("Character")->textureID = LoadTGA("Image//character.tga");

	entity.GetAnimator()->AddAnimation("WalkUp", "Character", 1, 9, 1.f, -1);
	entity.GetAnimator()->PlayAnimation("WalkUp");

	cout << "CBattleState loaded\n" << endl;

    /*
    	int Str;
	int Vit;
	int Int;
	int Mind;
	int Dex;
	int Agi;
	int Level;
	int statPoints;
    */
    testEntity = new BattleEntity();
    testEntity->GetInfo()->stats.AddVit(5);
    testEntity->GetInfo()->stats.AddStr(10);
    testEntity->GetInfo()->stats.AddInt(5);
    testEntity->GetInfo()->stats.AddMind(20);
    testEntity->GetInfo()->stats.AddDex(10);
    testEntity->GetInfo()->stats.AddAgi(20);
    testEntity->GetInfo()->stats.AddLevel(2);
    testEntity->GetInfo()->stats.UpdateStats();
    testEntity->GetInfo()->HP = testEntity->GetInfo()->stats.GetMaxHP();
    testEntity->GetInfo()->stats.GetRechargeRate();

    testEntity2 = new BattleEntity();
    //testEntity2->GetInfo()->HP = 100;
    testEntity2->GetInfo()->stats.AddVit(10);
    testEntity2->GetInfo()->stats.AddStr(20);
    testEntity2->GetInfo()->stats.AddInt(15);
    testEntity2->GetInfo()->stats.AddMind(50);
    testEntity2->GetInfo()->stats.AddDex(5);
    testEntity2->GetInfo()->stats.AddAgi(10);
    testEntity2->GetInfo()->stats.AddLevel(2);
    testEntity2->GetInfo()->stats.UpdateStats();
    testEntity2->GetInfo()->HP = testEntity2->GetInfo()->stats.GetMaxHP();

    testingBattle = new BattleSystem();

    testingBattle->BattleList.push_back(testEntity);
    testingBattle->BattleList.push_back(testEntity2);
    //BattleList.push_back(testEntity);
    //BattleList.push_back(testEntity2);
    //testEntity->GetInfo()->stats.UpdateStats();


}
void CBattleState::Update()
{
    // Fills up the Attack bar until a unit hits it first

    //if (atkbar_ >= 100)
    //PlayerCommand();

    if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
        encounter = true;

    //if (state != NULL)
    //    DetermineAction();
    if (encounter)
    {
        testingBattle->Update();
    }

	entity.Update();
}

void CBattleState::DetermineAction()
{
    turnbarfill = false;
    if (health_ <= 50)
        state = DEFEND;
    else
        state = ATTACK;
}

void CBattleState::DetermineAction2()
{
    turnbarfill = false;
    if (health2_ <= 20)
        state2 = DEFEND;
    else
        state2 = ATTACK;
}

// When battle start, start filling everyone's attack turn bar base on their rate
void CBattleState::AttackBarFill(double dt)
{
    // Iterate Through Entity List to fill up each and every Attack Bar
    atkbar_ += dt * (float)fillrate;
    atkbar2_ += dt *(float)fillrate2;
    //std::cout << atkbar_ << std::endl;
    //std::cout << atkbar2_ << std::endl;
    // checks if player, player then pop up the command, else monster will pewpew directly
}

// If it's Player's Turn
void CBattleState::PlayerCommand()
{
    if (atkbar_ >= 100)
        DetermineAction();

    if (atkbar2_ >= 100)
        DetermineAction2();

    if (state == ATTACK)
    {
        if (state2 != IDLE)
            health2_ -= (attack_ - (defense2_ * state2));
        else
            health2_ -= (attack_ - defense2_);

        if (health2_ <= 0)
            state2 = DEAD;
        state = IDLE;
        atkbar_ = 0;
        turnbarfill = true;
    }
    else if (state == DEFEND)
    {
        state = DEFEND;
        atkbar_ = 0;
        turnbarfill = true;
    }
    //else if (state == SKILL)
    //{

    //}
    if (state2 == ATTACK)
    {
        if (state != IDLE)
            health_ -= (attack2_ - (defense_ * state));
        else
            health_ -= (attack2_ - defense_);

        if (health_ <= 0)
            state = DEAD;
        state2 = IDLE;
        atkbar2_ = 0;
        turnbarfill = true;
    }
    else if (state2 == DEFEND)
    {
        state = DEFEND;
        atkbar2_ = 0;
        turnbarfill = true;
    }

    std::cout << health_ << std::endl;
    std::cout << health2_ << std::endl;

    //if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
    //{
    //    state = ATTACK;
    //    atkbar_ = 0;
    //    position_.Set(100, 20);
    //    TestEnemy->SetPosition(Vector3(position_.x, position_.y, 1.f));
    //}
    //if (KeyboardController::GetInstance()->IsKeyPressed(VK_NUMPAD2))
    //{
    //    state = DEFEND;
    //    atkbar_ = 0;
    //}
    //if (KeyboardController::GetInstance()->IsKeyPressed(VK_NUMPAD3))
    //{
    //    state = PASS;
    //    atkbar_ = 0;
    //}
}

void CBattleState::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GraphicsManager::GetInstance()->AttachCamera(&camera);
	// Setup 2D pipeline then render 2D
	GraphicsManager::GetInstance()->SetOrthographicProjection(0,
		Application::GetInstance().GetWindowWidth(),
		0,
		Application::GetInstance().GetWindowHeight(),
		-10, 10);
	entity.Render();
	GraphicsManager::GetInstance()->DetachCamera();

	// Render the required entities
	BattleStateBackground->RenderUI();
    TestEnemy->RenderUI();
    if (!turnbarfill)
        CommandBox->RenderUI();

    if (encounter)
    {
        testingBattle->Render();
    }
}
void CBattleState::Exit()
{
	// Remove the meshes which are specific to CBattleState
	MeshBuilder::GetInstance()->RemoveMesh("BattleState_BKGROUND");
    MeshBuilder::GetInstance()->RemoveMesh("Commandselect");
    MeshBuilder::GetInstance()->RemoveMesh("enemysprite");

	delete BattleStateBackground;
    delete CommandBox;
    delete TestEnemy;
	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
}