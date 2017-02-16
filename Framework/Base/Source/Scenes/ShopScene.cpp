#include <iostream>
#include "ShopScene.h"
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

ShopScene::ShopScene()
{

}
ShopScene::~ShopScene()
{

}

void ShopScene::Init()
{
	// Create and attach the camera to the scene
	camera.Init(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	// Load all the meshes
	MeshBuilder::GetInstance()->GenerateQuad("INTROSTATE_BKGROUND", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("INTROSTATE_BKGROUND")->textureID = LoadTGA("Image//splash.tga");

	MeshBuilder::GetInstance()->GenerateQuad("button_background", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("button_background")->textureID = LoadTGA("Image//Buttons//button_background.tga");

	MeshBuilder::GetInstance()->GenerateQuad("button_background_alt", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("button_background_alt")->textureID = LoadTGA("Image//Buttons//button_background_alt.tga");

	MeshBuilder::GetInstance()->GenerateText("text", 16, 16);
	MeshBuilder::GetInstance()->GetMesh("text")->textureID = LoadTGA("FontData//pixelFont.tga");
	MeshBuilder::GetInstance()->GetMesh("text")->material.kAmbient.Set(1, 0, 0);
	
	MeshBuilder::GetInstance()->GenerateQuad("Collider", Color(1.f, 0.f, 0.f));

	EntityFactory::GetInstance()->AttachEntityManager(&EManager);

	Lua->LoadFile("Sound");
	//SoundEngine::GetInstance()->SetMasterVolume(CLuaInterface::GetInstance()->GetFloatValue("BGM_Volume"));
	//SoundEngine::GetInstance()->AddRepeatSound("splash_bgm", "Sound/splash_bgm.mp3", 1.f);
	//SoundEngine::GetInstance()->Play("splash_bgm");

	float windowWidth = Application::GetInstance().GetWindowWidth();
	float windowHeight = Application::GetInstance().GetWindowHeight();

	IntroStateBackground = EntityFactory::GetInstance()->CreateSprite("INTROSTATE_BKGROUND", SpriteEntity::MODE_2D);
	IntroStateBackground->SetPosition(Vector3(windowWidth * 0.5f, windowHeight * 0.5f, 0.f));
	IntroStateBackground->SetScale(Vector3(windowWidth, windowHeight, 0.f));

	MeshBuilder::GetInstance()->GenerateSpriteAnimation("Character", 4, 9);
	MeshBuilder::GetInstance()->GetMesh("Character")->textureID = LoadTGA("Image//character.tga");

	cout << "ShopScene loaded\n" << endl;

	menu = new Menu();

	/*Button *btn1 = new Button();
	btn1->SetPosition(10, 10);
	btn1->SetImage(MeshBuilder::GetInstance()->GetMesh("Character"));
	btn1->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("Character"));
	menu->AddButton(btn1);*/

	HealthPotion* nigga = new HealthPotion();

	//string lmao = "   [IMAGE]  |  ";//[	 ITEM NAME	] | [6969] | Lorem ipsum dolor sit amet, consectetur adipiscing elit sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ";
	string lmao = "|  Item  |      Name     |  Gold  |          Description          |";

	Button* btn = new Button();
	btn->SetPosition(windowWidth * 0.5f, windowHeight - 80);
	//btn->SetTextOffset(50, 0);
	btn->SetScale(0, 0);
	//btn->SetImage(MeshBuilder::GetInstance()->GetMesh("INTROSTATE_BKGROUND"));
	//btn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("Character"));
	btn->SetText(lmao);
	menu->AddButton(btn);

	/*Button* btn1= new Button();
	btn1->SetPosition(Math::RandFloatMinMax(250, 0), Math::RandFloatMinMax(250, 500));
	btn1->SetTextOffset(50, 0);
	btn1->SetScale(250, 80);
	btn1->SetImage(MeshBuilder::GetInstance()->GetMesh("INTROSTATE_BKGROUND"));
	btn1->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("Character"));
	btn1->SetFunction(ButtonFunc);
	btn1->SetText(lmao);
	menu->AddButton(btn1);

	Button* btn3 = new Button();
	btn3->SetPosition(Math::RandFloatMinMax(250, 500), Math::RandFloatMinMax(250, 500));
	btn3->SetTextOffset(50, 0);
	btn3->SetScale(250, 80);
	btn3->SetImage(MeshBuilder::GetInstance()->GetMesh("INTROSTATE_BKGROUND"));
	btn3->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("Character"));
	btn3->SetFunction(ButtonFunc);
	btn3->SetText(lmao);
	menu->AddButton(btn3);*/

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
	swordy->SetName("Black Sword");
	swordy->SetDescription("What a black sword.");
	inventory->AddItem(swordy);

	inventory->PrintInventory();
	std::cout << inventory->UseItem(5, new CharacterInfo()) << std::endl;
	inventory->PrintInventory();

	for (unsigned i = 0; i < inventory->m_inventoryList.size(); ++i)
	{
		Button* btn = new Button();
		btn->SetPosition(windowWidth * 0.5f, windowHeight - 120 - i * 50);
		//btn->SetTextOffset(50, 0);
		btn->SetScale(1200, 40);
		btn->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
		btn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
		string lmaoooo = "|  ICON  | " + inventory->m_inventoryList[i]->GetName() + " | " + std::to_string(inventory->m_inventoryList[i]->GetGoldValue()) + " | " + inventory->m_inventoryList[i]->GetDescription();
		btn->SetText(lmaoooo);
		menu->AddButton(btn);
	}
}
void ShopScene::Update()
{
	float dt = StopWatch::GetInstance()->GetDeltaTime();
	camera.Update(dt);

	menu->Update();
	EManager.Update();

	if (KeyboardController::GetInstance()->IsKeyPressed(VK_ESCAPE))
		SceneManager::GetInstance()->quit = true;
}
void ShopScene::Render()
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
void ShopScene::Exit()
{
	// Remove the meshes which are specific to ShopScene
	MeshBuilder::GetInstance()->RemoveMesh("INTROSTATE_BKGROUND");

	EManager.ClearEntityList();

	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
}

///Button Functions
void ButtonFunction()
{
	
}