#include <iostream>
#include "introstate.h"
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
#include "../Entity/Entity2D.h"

#include "Collider\Collider_2DAABB.h"

using namespace std;

CIntroState::CIntroState()
{

}
CIntroState::~CIntroState()
{

}

void CIntroState::Init()
{
	// Create and attach the camera to the scene
	camera.Init(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	// Load all the meshes
	MeshBuilder::GetInstance()->GenerateQuad("INTROSTATE_BKGROUND", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("INTROSTATE_BKGROUND")->textureID = LoadTGA("Image//splash.tga");

	MeshBuilder::GetInstance()->GenerateText("text", 16, 16);
	MeshBuilder::GetInstance()->GetMesh("text")->textureID = LoadTGA("FontData//pixelFont.tga");
	MeshBuilder::GetInstance()->GetMesh("text")->material.kAmbient.Set(1, 0, 0);
	
	EntityFactory::GetInstance()->AttachEntityManager(&EManager);

	Lua->LoadFile("Sound");
	SoundEngine::GetInstance()->SetMasterVolume(CLuaInterface::GetInstance()->GetFloatValue("BGM_Volume"));
	//SoundEngine::GetInstance()->AddRepeatSound("splash_bgm", "Sound/splash_bgm.mp3", 1.f);
	//SoundEngine::GetInstance()->Play("splash_bgm");

	float windowWidth = Application::GetInstance().GetWindowWidth();
	float windowHeight = Application::GetInstance().GetWindowHeight();

	IntroStateBackground = EntityFactory::GetInstance()->CreateSprite("INTROSTATE_BKGROUND", SpriteEntity::MODE_2D);
	IntroStateBackground->SetPosition(Vector3(windowWidth * 0.5f, windowHeight * 0.5f, 0.f));
	IntroStateBackground->SetScale(Vector3(windowWidth, windowHeight, 0.f));

	MeshBuilder::GetInstance()->GenerateSpriteAnimation("Character", 4, 9);
	MeshBuilder::GetInstance()->GetMesh("Character")->textureID = LoadTGA("Image//character.tga");

	cout << "CIntroState loaded\n" << endl;

	menu = new Menu();

	/*Button *btn1 = new Button();
	btn1->SetPosition(10, 10);
	btn1->SetImage(MeshBuilder::GetInstance()->GetMesh("Character"));
	btn1->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("Character"));
	menu->AddButton(btn1);*/

	HealthPotion* nigga = new HealthPotion();

	string lmao = "   [IMAGE]  |  ";//[	 ITEM NAME	] | [6969] | Lorem ipsum dolor sit amet, consectetur adipiscing elit sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ";
	lmao = lmao + nigga->GetName() + "  |  " + std::to_string(nigga->GetGoldValue()) + "  |  " + nigga->GetDescription();

	/*btn2 = new Button();
	btn2->SetPosition(windowWidth * 0.5f, windowHeight * 0.5f);
	btn2->SetTextOffset(50, 0);
	btn2->SetScale(250, 80);
	btn2->SetImage(MeshBuilder::GetInstance()->GetMesh("INTROSTATE_BKGROUND"));
	btn2->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("Character"));
	btn2->SetText(lmao);
	menu->AddButton(btn2);

	Button* btn1= new Button();
	btn1->SetPosition(Math::RandFloatMinMax(250, 0), Math::RandFloatMinMax(250, 500));
	btn1->SetTextOffset(50, 0);
	btn1->SetScale(250, 80);
	btn1->SetImage(MeshBuilder::GetInstance()->GetMesh("INTROSTATE_BKGROUND"));
	btn1->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("Character"));
	btn1->SetText(lmao);
	menu->AddButton(btn1);

	Button* btn3 = new Button();
	btn3->SetPosition(Math::RandFloatMinMax(250, 500), Math::RandFloatMinMax(250, 500));
	btn3->SetTextOffset(50, 0);
	btn3->SetScale(250, 80);
	btn3->SetImage(MeshBuilder::GetInstance()->GetMesh("INTROSTATE_BKGROUND"));
	btn3->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("Character"));
	btn3->SetText(lmao);
	menu->AddButton(btn3);*/

	/*Entity2D* littleFucker = new Entity2D();
	littleFucker->GetAnimator()->AddAnimation("RUN", new Animation("Character", 0, 8, 1.f, -1));
	littleFucker->GetAnimator()->PlayAnimation("RUN");
	littleFucker->SetScale(Vector3(50.f, 50.f, 1.f));
	littleFucker->SetPosition(Vector3(windowWidth * 0.5f, windowHeight * 0.5f, 1.f));
	EManager.AddEntity(littleFucker);*/

	//Initialise inventory
	inventory = new Inventory();

	//Some random potions
	inventory->AddItem(new HealthPotion());
	inventory->AddItem(new HealthPotion());
	inventory->AddItem(new HealthPotion());
	inventory->AddItem(new MaxHealthPotion());

	//A special item
	HealthPotion* specialPotion = new HealthPotion();
	specialPotion->SetName("LingLongDingDong");
	inventory->AddItem(specialPotion);

	Equipment *swordy = new Equipment(TYPE_WEAPON, 10, 0, 0, 0);
	swordy->SetName("Sword of Niggers");
	swordy->SetDescription("This sword is going to steal shit topkeku.");
	inventory->AddItem(swordy);

	inventory->PrintInventory();

	std::cout << inventory->UseItem(5, new CharacterInfo()) << std::endl;

	inventory->PrintInventory();


	/*CharacterInfo* chara = new CharacterInfo();
	chara->name = "dogshit";
	chara->stats.AddAgi(Math::RandIntMinMax(0,10));
	chara->stats.AddStr(Math::RandIntMinMax(0,10));
	chara->stats.AddDex(Math::RandIntMinMax(0,10));
	chara->stats.AddMind(Math::RandIntMinMax(0,10));
	chara->stats.AddVit(Math::RandIntMinMax(0,10));
	chara->stats.AddInt(Math::RandIntMinMax(0,10));
	chara->stats.UpdateStats();
	chara->HP = 69;

	std::cout << std::endl;

	std::cout << chara->name << "\'s " << "current health: " << chara->HP << " / " << chara->stats.GetMaxHP() << std::endl;
	inventory->UseItem(3, chara);
	std::cout << chara->name << "\'s " << "current health: " << chara->HP << " / "<< chara->stats.GetMaxHP() << std::endl;*/

}
void CIntroState::Update()
{
	if (KeyboardController::GetInstance()->IsKeyReleased(VK_SPACE))
	{
		//cout << "Loading MenuState" << endl;
		//SceneManager::GetInstance()->SetActiveScene("MenuState");
	}
	
	float dt = StopWatch::GetInstance()->GetDeltaTime();
	camera.Update(dt);

	menu->Update();
	EManager.Update();

	if (KeyboardController::GetInstance()->IsKeyPressed(VK_ESCAPE))
		SceneManager::GetInstance()->quit = true;
}
void CIntroState::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GraphicsManager::GetInstance()->AttachCamera(&camera);
	// Setup 2D pipeline then render 2D
	GraphicsManager::GetInstance()->SetOrthographicProjection(0, 
															  Application::GetInstance().GetWindowWidth(), 
															  0, 
															  Application::GetInstance().GetWindowHeight(), 
															  -10, 10);

	GraphicsManager::GetInstance()->DetachCamera();
	EManager.Render();

	// Render the required entities
	menu->Render();

	//EManager.RenderUI();

}
void CIntroState::Exit()
{
	// Remove the meshes which are specific to CIntroState
	MeshBuilder::GetInstance()->RemoveMesh("INTROSTATE_BKGROUND");

	EManager.ClearEntityList();

	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();

}

///Button Functions
void ButtonFunc()
{
	btn2->SetPosition(Math::RandFloatMinMax(250, 500), Math::RandFloatMinMax(250, 500));
	//btn2->SetScale(Math::RandFloatMinMax(10, 300), Math::RandFloatMinMax(10, 300));
}