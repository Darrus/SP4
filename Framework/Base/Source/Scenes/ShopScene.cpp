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

#include "../Animation/AnimationsContainer.h"

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

	MeshBuilder::GetInstance()->GenerateQuad("Gold", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("Gold")->textureID = LoadTGA("Image//Gold.tga");

	MeshBuilder::GetInstance()->GenerateText("text", 16, 16);
	MeshBuilder::GetInstance()->GetMesh("text")->textureID = LoadTGA("FontData//pixelFont.tga");
	MeshBuilder::GetInstance()->GetMesh("text")->material.kAmbient.Set(1, 0, 0);
	
	MeshBuilder::GetInstance()->GenerateQuad("Collider", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//collider.tga");

	EntityFactory::GetInstance()->AttachEntityManager(&EManager);

	float windowWidth = Application::GetInstance().GetWindowWidth();
	float windowHeight = Application::GetInstance().GetWindowHeight();

	MeshBuilder::GetInstance()->GenerateSpriteAnimation("Character", 4, 9);
	MeshBuilder::GetInstance()->GetMesh("Character")->textureID = LoadTGA("Image//character.tga");

	cout << "ShopScene loaded\n" << endl;

	MeshBuilder::GetInstance()->GenerateSpriteAnimation("character", 4, 9)->textureID = LoadTGA("Image//character.tga");

	acceptpurchase = false;  

	//init inventory
	shop_inventory = new Inventory();
	cart_inventory = new Inventory();
	player_inventory = new Inventory();

	//init Menus
	utilitybuttons = new Menu();

	shop_menu = new Shop_Menu();
	shop_menu->SetItemsPerPage(4);
	shop_menu->SetStoreInventory(shop_inventory);
	shop_menu->SetCartInventory(cart_inventory);
	shop_menu->SetPosition(500, 850);

	cart_menu = new Cart_Menu();
	cart_menu->SetNumberItemsPerRow(9);
	cart_menu->SetPosition(1000.0f, 850.0f);
	cart_menu->SetTargetInventory(*cart_inventory);

	//Some items in the "Shop"
	shop_inventory->AddItem(new HealthPotion());
	shop_inventory->AddItem(new HealthPotion());	
	shop_inventory->AddItem(new MaxHealthPotion());
	shop_inventory->AddItem(new HealthPotion());
	shop_inventory->AddItem(new HealthPotion());	
	shop_inventory->AddItem(new MaxHealthPotion());
	shop_inventory->AddItem(new HealthPotion());
	shop_inventory->AddItem(new MaxHealthPotion());
	shop_inventory->AddItem(new MaxHealthPotion());	
	shop_inventory->AddItem(new MaxHealthPotion());
	shop_inventory->AddItem(new MaxHealthPotion());

	//A special item
	HealthPotion* specialPotion = new HealthPotion();
	specialPotion->SetName("LingLongDingDong");
	specialPotion->SetMesh(MeshBuilder::GetInstance()->GetMesh("character"));
	shop_inventory->AddItem(specialPotion);

	//An equipment item
	Equipment *swordy = new Equipment(TYPE_WEAPON, 10, 0, 0, 0);
	swordy->SetName("Black Sword");
	swordy->SetDescription("What a black sword.");
	swordy->SetMesh(MeshBuilder::GetInstance()->GetMesh("INTROSTATE_BKGROUND"));
	shop_inventory->AddItem(swordy);
	
	//Utility buttons
	SetBool_Button* acceptpurchasebtn = new SetBool_Button();
	acceptpurchasebtn->SetSwitch(acceptpurchase);
	acceptpurchasebtn->SetBoolean(true);
	acceptpurchasebtn->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	acceptpurchasebtn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	acceptpurchasebtn->SetText("Accept Purchase");
	acceptpurchasebtn->SetTextOffset(70, 00);
	acceptpurchasebtn->SetScale(400, 100);
	acceptpurchasebtn->SetPosition(1400, 100);
	utilitybuttons->AddButton(acceptpurchasebtn);

	//Bttons to scroll thru pages of the shop
	Increment_Button* nextpage = new Increment_Button();
	nextpage->SetTargetValue(currentPage);
	nextpage->SetIncrementAmount(1);
	nextpage->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	nextpage->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	nextpage->SetText("Next\npage");
	nextpage->SetScale(200, 100);
	nextpage->SetPosition(700, 100);
	nextpage->SetTextOffset(60, 15);
	utilitybuttons->AddButton(nextpage);

	Increment_Button* prevpage = new Increment_Button();
	prevpage->SetTargetValue(currentPage);
	prevpage->SetIncrementAmount(-1);
	prevpage->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	prevpage->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	prevpage->SetText("Previous\n  page");
	prevpage->SetScale(200, 100);
	prevpage->SetPosition(300, 100);
	prevpage->SetTextOffset(35, 15);
	utilitybuttons->AddButton(prevpage);

	//Exit back to overworld button
	ChangeScene_Button* changeScene = new ChangeScene_Button();
	changeScene->SetDesiredScene("Overworld");
	changeScene->SetText("Exit");
	changeScene->SetTextOffset(35, 0);
	changeScene->SetScale(140, 100);
	changeScene->SetPosition(1850, 1000);
	changeScene->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	changeScene->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	utilitybuttons->AddButton(changeScene);

	ChangeValue_Button* backbtn = new ChangeValue_Button();
	backbtn->SetText("Back");
	backbtn->SetTextOffset(50, 0);
	backbtn->SetScale(150, 100);
	backbtn->SetPosition(50, 1000);
	backbtn->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	backbtn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	utilitybuttons->AddButton(backbtn);

	//Get Menus to create their own buttons
	shop_menu->SetCurrentPage(currentPage);
	shop_menu->UpdateButtonPositions();

	cart_menu->InitialiseButtons();
}
void ShopScene::Update()
{
	/*TODO:
	--------------------------------------------
	This should be handled in a containter class
	--------------------------------------------
	To include in the container class:
	-Cart Inventory
	-Cart Menu
	-Positon
	-Animation functions -->> This should be done in the scene itself
	-Confirm purchase / Add to inventory button
	->Add a Prompt for confirmation
	->Reject if player does not have enough gold */
	if (acceptpurchase)
	{
		for (unsigned i = 0; i < cart_inventory->m_inventoryList.size(); ++i)
			player_inventory->AddItem(cart_inventory->m_inventoryList[i]);

		for (auto it = cart_inventory->m_inventoryList.begin(); it != cart_inventory->m_inventoryList.end(); ++it)
			delete *it;

		cart_inventory->m_inventoryList.clear();

		acceptpurchase = false;
	}

	float dt = StopWatch::GetInstance()->GetDeltaTime();
	camera.Update(dt);

	utilitybuttons->Update();
	shop_menu->Update();
	cart_menu->Update();
	EManager.Update();

	//Cheat keys
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

	// Render stuff
	EManager.Render();
	shop_menu->Render();
	utilitybuttons->Render();
	cart_menu->Render();
	
	//For the page
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(465, 95, 0);
	modelStack.Scale(70.f, 70.f, 10.f);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), std::to_string(currentPage + 1), Color(0, 1, 0));
	modelStack.PopMatrix();
	EManager.RenderUI();

}
void ShopScene::Exit()
{
	// Remove the meshes which are specific to ShopScene
	MeshBuilder::GetInstance()->RemoveMesh("INTROSTATE_BKGROUND");

	EManager.ClearEntityList();

	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
}