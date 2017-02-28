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
   
    //testEntity = new BattleEntity();
    //testEntity->GetInfo()->stats.AddVit(50);
    //testEntity->GetInfo()->stats.AddStr(40);
    //testEntity->GetInfo()->stats.AddInt(5);
    //testEntity->GetInfo()->stats.AddMind(20);
    //testEntity->GetInfo()->stats.AddDex(10);
    //testEntity->GetInfo()->stats.AddAgi(7);
    //testEntity->GetInfo()->stats.AddLevel(2);
    //testEntity->GetInfo()->name = "Triple H";
    //testEntity->GetInfo()->id = 3;
    //testEntity->enemyType = BattleEntity::ENEMY;
    //testEntity->GetInfo()->stats.UpdateStats();
    //testEntity->SetPosition(Vector3(windowWidth * 0.25f, windowHeight * 0.5f, 1.f));
    //testEntity->GetInfo()->HP = testEntity->GetInfo()->stats.GetMaxHP();

    //testEntity2 = new BattleEntity();
    //testEntity2->GetInfo()->stats.AddVit(50);
    //testEntity2->GetInfo()->stats.AddStr(50);
    //testEntity2->GetInfo()->stats.AddInt(15);
    //testEntity2->GetInfo()->stats.AddMind(50);
    //testEntity2->GetInfo()->stats.AddDex(40);
    //testEntity2->GetInfo()->stats.AddAgi(2);
    //testEntity2->GetInfo()->stats.AddLevel(2);
    //testEntity2->GetInfo()->name = "John Cena";
    //testEntity2->GetInfo()->id = 4;
    //testEntity2->enemyType = BattleEntity::ENEMY;
    //testEntity2->GetInfo()->stats.UpdateStats();
    //testEntity2->SetPosition(Vector3(windowWidth * 0.25f, windowHeight * 0.25f, 1.f));
    //testEntity2->GetInfo()->HP = testEntity2->GetInfo()->stats.GetMaxHP();

    //BattleList.push_back(testEntity);
    //BattleList.push_back(testEntity2);
    //testEntity->GetInfo()->stats.UpdateStats();
    //party = new PartySystem();


    testingBattle = new BattleSystem();
    charahehe = new CharacterInfo();
    party = new PartySystem();

    charahehe->stats.AddVit(10);
    charahehe->stats.AddStr(8);
    charahehe->stats.AddInt(6);
    charahehe->stats.AddMind(5);
    charahehe->stats.AddDex(11);
    charahehe->stats.AddAgi(3);
    charahehe->stats.AddLevel(5);
    charahehe->name = "Randall";
    charahehe->id = 0;
    charahehe->stats.UpdateStats();
    charahehe->HP = charahehe->stats.GetMaxHP();
    charahehe->MP = charahehe->stats.GetMaxMP();
    SkillContainer::GetInstance()->Init();
    charahehe->skills.push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
    charahehe->skills.push_back(SkillContainer::GetInstance()->GetSkill("Fire Blast"));
    //testingBattle->partypew->AddMember(charahehe);
    party->AddMember(charahehe);

    charahehe = new CharacterInfo();
    charahehe->stats.AddVit(4);
    charahehe->stats.AddStr(6);
    charahehe->stats.AddInt(7);
    charahehe->stats.AddMind(15);
    charahehe->stats.AddDex(8);
    charahehe->stats.AddAgi(1);
    charahehe->stats.AddLevel(5);
    charahehe->name = "Darrus";
    charahehe->id = 1;
    charahehe->stats.UpdateStats();
    charahehe->HP = charahehe->stats.GetMaxHP();
    charahehe->MP = charahehe->stats.GetMaxMP();
    charahehe->skills.push_back(SkillContainer::GetInstance()->GetSkill("Hero Maker"));
    charahehe->skills.push_back(SkillContainer::GetInstance()->GetSkill("Fire Blast"));
    charahehe->skills.push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
    //testingBattle->partypew->AddMember(charahehe);
    party->AddMember(charahehe);

    charahehe = new CharacterInfo();
    charahehe->stats.AddVit(5);
    charahehe->stats.AddStr(6);
    charahehe->stats.AddInt(4);
    charahehe->stats.AddMind(3);
    charahehe->stats.AddDex(7);
    charahehe->stats.AddAgi(10);
    charahehe->stats.AddLevel(5);
    charahehe->name = "Reuben";
    charahehe->id = 2;
    charahehe->stats.UpdateStats();
    charahehe->HP = charahehe->stats.GetMaxHP();
    charahehe->MP = charahehe->stats.GetMaxMP();
    charahehe->skills.push_back(SkillContainer::GetInstance()->GetSkill("Sweep"));
    charahehe->skills.push_back(SkillContainer::GetInstance()->GetSkill("Fire Blast"));
    charahehe->skills.push_back(SkillContainer::GetInstance()->GetSkill("Hero Maker"));
    charahehe->skills.push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
    party->AddMember(charahehe);
    //testingBattle->partypew->AddMember(charahehe);

    Player::GetInstance().SetParty(*party);

    testingBattle->AssignPlayerParty();

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

        testingBattle->AssignPlayerParty();

        int randenemy = Math::RandIntMinMax(1, 4);

        for (int rand = 0; rand < randenemy; rand++)
        {
            enemyhehe = efactory->CreateRandomEnemy((Player::GetInstance().GetParty()->memberCount() - 1) + rand);
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