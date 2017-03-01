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

#include "../Animation/AnimationsContainer.h"

#include "../Player/Player.h"

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

	float windowWidth = Application::GetInstance().GetWindowWidth();
	float windowHeight = Application::GetInstance().GetWindowHeight();

	MeshBuilder::GetInstance()->GenerateSpriteAnimation("Character", 4, 9);
	MeshBuilder::GetInstance()->GetMesh("Character")->textureID = LoadTGA("Image//character.tga");

	cout << "ShopScene loaded\n" << endl;

	MeshBuilder::GetInstance()->GenerateSpriteAnimation("character", 4, 9)->textureID = LoadTGA("Image//character.tga");

	b_accept = false;
	buying_tab = true;

	//init inventory
	shop_inventory = new Inventory();
	cart_inventory = new Inventory();
	player_inventory = Player::GetInstance().GetInventory();

	//init Menus
	utilitybuttons = new Menu();

	//For buying
	shop_menu = new Shop_Menu();
	shop_menu->SetItemsPerPage(4);
	shop_menu->SetStoreInventory(shop_inventory);
	shop_menu->SetCartInventory(cart_inventory);
	shop_menu->SetPosition(500, 850);

	cart_menu = new Cart_Menu();
	cart_menu->SetNumberItemsPerRow(9);
	cart_menu->SetPosition(1000.0f, 850.0f);
	cart_menu->SetTargetInventory(*cart_inventory);

	//For selling
	player_selling_menu = new SellingCart_Menu();
	player_selling_menu->SetNumberItemsPerRow(7);
	player_selling_menu->SetPosition(200.0f, 850.0f);
	player_selling_menu->SetTargetInventory(*player_inventory);
	player_selling_menu->SetReceivingInventory(*cart_inventory);

	shop_selling_menu = new SellingCart_Menu();
	shop_selling_menu->SetNumberItemsPerRow(9);
	shop_selling_menu->SetPosition(1000.0f, 850.0f);
	shop_selling_menu->SetTargetInventory(*cart_inventory);
	shop_selling_menu->SetReceivingInventory(*player_inventory);

	cart_cost = 0;

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
	acceptpurchasebtn = new SetBool_Button();
	acceptpurchasebtn->SetSwitch(b_accept);
	acceptpurchasebtn->SetBoolean(true);
	acceptpurchasebtn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	acceptpurchasebtn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	acceptpurchasebtn->SetText("Accept Purchase");
	acceptpurchasebtn->SetTextOffset(70, 00);
	acceptpurchasebtn->SetScale(400, 100);
	acceptpurchasebtn->SetPosition(1400, 100);
	utilitybuttons->AddButton(acceptpurchasebtn);

	//Buttons to scroll thru pages of the shop
	Increment_Button* nextpage = new Increment_Button();
	nextpage->SetTargetValue(currentPage);
	nextpage->SetIncrementAmount(1);
	nextpage->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	nextpage->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	nextpage->SetText("Next\npage");
	nextpage->SetScale(200, 100);
	nextpage->SetPosition(700, 100);
	nextpage->SetTextOffset(60, 15);
	shop_menu->SetNextButton(nextpage);

	Increment_Button* prevpage = new Increment_Button();
	prevpage->SetTargetValue(currentPage);
	prevpage->SetIncrementAmount(-1);
	prevpage->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	prevpage->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	prevpage->SetText("Previous\n  page");
	prevpage->SetScale(200, 100);
	prevpage->SetPosition(300, 100);
	prevpage->SetTextOffset(35, 15);
	shop_menu->SetPreviousButton(prevpage);

	//Exit back to overworld button
	ChangeScene_Button* changeScene = new ChangeScene_Button();
	changeScene->SetDesiredScene("TownShop");
	changeScene->SetText("Exit");
	changeScene->SetTextOffset(35, 0);
	changeScene->SetScale(140, 100);
	changeScene->SetPosition(1850, 1000);
	changeScene->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	changeScene->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	utilitybuttons->AddButton(changeScene);

	PreviousScene_Button* backbtn = new PreviousScene_Button();
	backbtn->SetText("Back");
	backbtn->SetTextOffset(50, 0);
	backbtn->SetScale(150, 100);
	backbtn->SetPosition(50, 1000);
	backbtn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	backbtn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	utilitybuttons->AddButton(backbtn);

	prompt = new PopUp_Button();
	prompt->SetActive(false);
	prompt->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	prompt->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	prompt->SetText("You do not have enough gold to make this purchase\n\nClick this button to continue.");
	prompt->SetScale(1000, 600);
	prompt->SetPosition(900, 540);
	utilitybuttons->AddButton(prompt);

	//Toggle between Buying and Selling
	tgle_btn = new Toggle_Button();
	tgle_btn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	tgle_btn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	tgle_btn->SetText("Buying");
	tgle_btn->SetAlternateText("Selling");
	tgle_btn->SetSwitch(buying_tab);
	tgle_btn->SetScale(200, 100);
	tgle_btn->SetPosition(Application::GetInstance().GetWindowWidth() * 0.5, 1050);
	utilitybuttons->AddButton(tgle_btn);

	//Get Menus to create their own buttons
	shop_menu->SetCurrentPage(currentPage);
	shop_menu->UpdateButtonPositions();

	cart_menu->InitialiseButtons();
	player_selling_menu->InitialiseButtons();
	shop_selling_menu->InitialiseButtons();

	cart_amount = new GUIObject();
	cart_amount->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	cart_amount->SetText("Total:");
	cart_amount->SetScale(300, 100);
	cart_amount->SetPosition(1100, 900);

	player_gold_amount = new GUIObject();
	player_gold_amount->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	player_gold_amount->SetText("Your Gold:");
	player_gold_amount->SetTextOffset(5, 20);
	player_gold_amount->SetScale(300, 100);
	player_gold_amount->SetPosition(1550, 900);

	inventory_display = new GUIObject();
	inventory_display->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	inventory_display->SetText("Shop\'s Inventory:");
	inventory_display->SetTextOffset(150, 0);
	inventory_display->SetScale(600, 80);
	inventory_display->SetPosition(500, 900);

	temp_player_gold = 9999;
}
void ShopScene::Update()
{
	float dt = StopWatch::GetInstance()->GetDeltaTime();
	camera.Update(dt);

	utilitybuttons->Update();

	//Always clear inventory when swapping between buying and selling
	if (tgle_btn->m_isPressed)
		cart_inventory->ClearInventory();

	if (buying_tab)
	{
		acceptpurchasebtn->SetText("Accept Purchase");
		inventory_display->SetText("Shop\'s Inventory:");

		cart_cost = 0;
		for (unsigned i = 0; i < cart_inventory->m_inventoryList.size(); ++i)
			cart_cost += cart_inventory->m_inventoryList[i]->GetGoldValue();

		//If player accepts the purchase
		if (b_accept)
		{
			if (cart_cost > temp_player_gold)
				prompt->SetActive(true);
			else
			{
				temp_player_gold -= cart_cost;

				for (unsigned i = 0; i < cart_inventory->m_inventoryList.size(); ++i)
					player_inventory->AddCopy(cart_inventory->m_inventoryList[i]);

				cart_inventory->ClearInventory();

				player_selling_menu->InitialiseButtons();
			}

			b_accept = false;
		}

		shop_menu->Update();
		cart_menu->Update();
	}
	else
	{
		acceptpurchasebtn->SetText("Sell");
		inventory_display->SetText("Your Inventory:");

		cart_cost = 0;
		for (unsigned i = 0; i < cart_inventory->m_inventoryList.size(); ++i)
			cart_cost += cart_inventory->m_inventoryList[i]->GetGoldValue();

		if (b_accept)
		{
			temp_player_gold += cart_cost;

			cart_inventory->ClearInventory();

			b_accept = false;
		}

		player_selling_menu->Update();
		shop_selling_menu->Update();
	}

	//Cheat keys
	if (KeyboardController::GetInstance()->IsKeyPressed(VK_ESCAPE))
		SceneManager::GetInstance()->quit = true;
	if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
		std::cout << cart_inventory->m_inventoryList.size() << std::endl;
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

	if (buying_tab)
	{
		shop_menu->Render();
		cart_menu->Render();
	}
	else
	{
		player_selling_menu->Render();
		shop_selling_menu->Render();
	}

	utilitybuttons->Render();
	
	//GUI Objects
	cart_amount->Render();
	player_gold_amount->Render();
	inventory_display->Render();

	//============================================================================================//
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	if (buying_tab)
	{
		modelStack.PushMatrix();
		modelStack.Translate(510, 100, 0);
		modelStack.Scale(100.f, 100.f, 1.f);
		RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("button_background"));
		modelStack.Translate(-0.45, 0, 0);
		modelStack.Scale(0.75f, 0.75f, 1.f);
		RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), std::to_string(currentPage + 1), Color(0, 1, 0));
		modelStack.PopMatrix();
	}
	//Cart cost
	modelStack.PushMatrix();
	modelStack.Translate(1050, 900, 0);
	modelStack.Scale(50.f, 50.f, 1.f);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), std::to_string(cart_cost), Color(0, 1, 0));
	modelStack.PopMatrix();

	//Player gold
	modelStack.PushMatrix();
	modelStack.Translate(1500, 880, 0);
	modelStack.Scale(50.f, 50.f, 1.f);
	//RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), std::to_string(Player::GetInstance().), Color(0, 1, 0));
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), std::to_string(temp_player_gold), Color(0, 1, 0));
	modelStack.PopMatrix();
	//============================================================================================//

	EManager.RenderUI();
}

void ShopScene::Exit()
{
	EManager.ClearEntityList();

	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
}

void ShopScene::Pause()
{
	currentPage = 0;
	prompt->SetActive(false);
}

void ShopScene::UnPause()
{
	shop_menu->SetCurrentPage(currentPage);
	shop_menu->UpdateButtonPositions();
	cart_menu->InitialiseButtons();
	player_selling_menu->InitialiseButtons();
	shop_selling_menu->InitialiseButtons();
}