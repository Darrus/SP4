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
#include "..\Overworld\Overworld.h"

// Utilities
#include "../Animation/AnimationsContainer.h"

#include "..\Items\Consumable.h"
#include "../Skills/SkillFunctions.h"

using namespace std;    

CBattleState::CBattleState() :
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
	MeshBuilder::GetInstance()->GetMesh("BattleState_BKGROUND")->textureID = LoadTGA("Image//battlebg.tga");

    MeshBuilder::GetInstance()->GenerateQuad("Commandselect", Color(1, 1, 1), 1.f);
    MeshBuilder::GetInstance()->GetMesh("Commandselect")->textureID = LoadTGA("Image//Buttons//button_background.tga");

    MeshBuilder::GetInstance()->GenerateQuad("Kayne West", Color(1, 1, 1), 1.f);
    MeshBuilder::GetInstance()->GetMesh("Kayne West")->textureID = LoadTGA("Image//enemy.tga");

    MeshBuilder::GetInstance()->GenerateQuad("Dwayne Johnson", Color(1, 1, 1), 1.f);
    MeshBuilder::GetInstance()->GetMesh("Dwayne Johnson")->textureID = LoadTGA("Image//enemy2.tga");

    MeshBuilder::GetInstance()->GenerateQuad("Carbonara", Color(1, 1, 1), 1.f);
    MeshBuilder::GetInstance()->GetMesh("Carbonara")->textureID = LoadTGA("Image//enemy3.tga");

    MeshBuilder::GetInstance()->GenerateQuad("King Moogle", Color(1, 1, 1), 1.f);
    MeshBuilder::GetInstance()->GetMesh("King Moogle")->textureID = LoadTGA("Image//enemy3.tga");


    MeshBuilder::GetInstance()->GenerateQuad("player1", Color(1, 1, 1), 1.f);
    MeshBuilder::GetInstance()->GetMesh("player1")->textureID = LoadTGA("Image//Player//player1.tga");

    MeshBuilder::GetInstance()->GenerateQuad("player2", Color(1, 1, 1), 1.f);
    MeshBuilder::GetInstance()->GetMesh("player2")->textureID = LoadTGA("Image//Player//player2.tga");

    MeshBuilder::GetInstance()->GenerateQuad("player3", Color(1, 1, 1), 1.f);
    MeshBuilder::GetInstance()->GetMesh("player3")->textureID = LoadTGA("Image//Player//player3.tga");

    MeshBuilder::GetInstance()->GenerateQuad("arrow", Color(1, 1, 1), 1.f);
    MeshBuilder::GetInstance()->GetMesh("arrow")->textureID = LoadTGA("Image//arrow.tga");

	MeshBuilder::GetInstance()->GenerateText("text", 16, 16);
    MeshBuilder::GetInstance()->GetMesh("text")->textureID = LoadTGA("FontData//pixelFont.tga");
	MeshBuilder::GetInstance()->GetMesh("text")->material.kAmbient.Set(1, 0, 0);

	//Lua->LoadFile("Sound");
	//SoundEngine::GetInstance()->SetMasterVolume(CLuaInterface::GetInstance()->GetFloatValue("BGM_Volume"));
	//SoundEngine::GetInstance()->AddRepeatSound("splash_bgm", "Sound/splash_bgm.mp3", 1.f);
	//SoundEngine::GetInstance()->Play("splash_bgm");

	float windowWidth = Application::GetInstance().GetWindowWidth();
	float windowHeight = Application::GetInstance().GetWindowHeight();

    BattleStateBackground = new SpriteEntity(MeshBuilder::GetInstance()->GetMesh("BattleState_BKGROUND"));
    BattleStateBackground->SetTextRenderMode(SpriteEntity::MODE_2D);
	BattleStateBackground->SetPosition(Vector3(windowWidth * 0.5f, windowHeight * 0.5f, 0.f));
	BattleStateBackground->SetScale(Vector3(windowWidth, windowHeight, 0.f));

    CommandBox = new SpriteEntity(MeshBuilder::GetInstance()->GetMesh("Commandselect"));
    CommandBox->SetTextRenderMode(SpriteEntity::MODE_2D);
    CommandBox->SetPosition(Vector3(windowWidth * 0.85f, windowHeight * 0.3f, 1.f));
    CommandBox->SetScale(Vector3(windowWidth * 0.2, windowHeight * 0.4, 0.f));

	MeshBuilder::GetInstance()->GenerateSpriteAnimation("character", 4, 9);
	MeshBuilder::GetInstance()->GetMesh("character")->textureID = LoadTGA("Image//character.tga");

	AnimationsContainer::GetInstance()->AddAnimation("walk", "character", 1, 9, 1.f, -1);

	entity.GetAnimator()->AddAnimation("walk");
	entity.GetAnimator()->PlayAnimation("walk");

	cout << "CBattleState loaded\n" << endl;

    testingBattle = new BattleSystem();
    //testingBattle->PlayerInfoList.clear();

    efactory = new MonsterFactory();

    testingBattle->EnemyInfoList.push_back(efactory->CreateEnemy2(3));
    testingBattle->EnemyInfoList.push_back(efactory->CreateEnemy1(4));
    testingBattle->AssignEnemies();

    Player::GetInstance().GetInventory()->AddItem(new HealthPotion());
    Player::GetInstance().GetInventory()->AddItem(new HealthPotion());
    Player::GetInstance().GetInventory()->AddItem(new HealthPotion());
    Player::GetInstance().GetInventory()->AddItem(new HealthPotion());
    Player::GetInstance().GetInventory()->AddItem(new HealthPotion());
    Player::GetInstance().GetInventory()->AddItem(new HealthPotion());
    Player::GetInstance().GetInventory()->AddItem(new HealthPotion());
    Player::GetInstance().GetInventory()->AddItem(new HealthPotion());
    Player::GetInstance().GetInventory()->AddItem(new HealthPotion());
    Player::GetInstance().GetInventory()->AddItem(new HealthPotion());
    Player::GetInstance().GetInventory()->AddItem(new HealthPotion());
    Player::GetInstance().GetInventory()->AddItem(new HealthPotion());
    Player::GetInstance().GetInventory()->AddItem(new HealthPotion());
    Player::GetInstance().GetInventory()->AddItem(new HealthPotion());
    Player::GetInstance().GetInventory()->AddItem(new HealthPotion());
    Player::GetInstance().GetInventory()->AddItem(new HealthPotion());
    Player::GetInstance().GetInventory()->AddItem(new HealthPotion());
    Player::GetInstance().GetInventory()->AddItem(new HealthPotion());
    Player::GetInstance().GetInventory()->AddItem(new MaxHealthPotion());
}

void CBattleState::Update()
{
    //if (testingBattle->CheckAnyAlive() != nullptr)
    testingBattle->Update();
    //entity.Update();

    if (testingBattle->CheckAnyAlive() == nullptr && Overworld::battle == false)
    {
        for (auto pewpew = testingBattle->EnemyList.begin(); pewpew != testingBattle->EnemyList.end(); pewpew++)
            delete (*pewpew);
        testingBattle->EnemyList.clear();
        testingBattle->EnemyInfoList.clear();

        for (auto pepepe = testingBattle->PlayerList.begin(); pepepe != testingBattle->PlayerList.end(); pepepe++)
            delete (*pepepe);

        testingBattle->PlayerList.clear();
        testingBattle->BattleList.clear();

        //testingBattle->AssignPlayerParty();

        int randenemy = Math::RandIntMinMax(1, 4);

        for (int rand = 0; rand < randenemy; rand++)
        {
            enemyhehe = efactory->CreateRandomEnemy((Player::GetInstance().GetParty()->memberCount()) + rand);
            testingBattle->EnemyInfoList.push_back(enemyhehe);
        }
        testingBattle->AssignEnemies();
    }
}

void CBattleState::Render()
{
	GraphicsManager::GetInstance()->SetOrthographicProjection(0,
		Application::GetInstance().GetWindowWidth(),
		0,
		Application::GetInstance().GetWindowHeight(),
		-10, 10);
    
    //if (testingBattle->CheckAnyAlive() != nullptr)
        testingBattle->Render();
}
void CBattleState::Exit()
{
	// Remove the meshes which are specific to CBattleState
	MeshBuilder::GetInstance()->RemoveMesh("BattleState_BKGROUND");
    MeshBuilder::GetInstance()->RemoveMesh("Commandselect");
    MeshBuilder::GetInstance()->RemoveMesh("enemysprite");

	delete BattleStateBackground;
    delete CommandBox;
	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
}

void CBattleState::UnPause()
{
    testingBattle->AssignPlayerParty();
}