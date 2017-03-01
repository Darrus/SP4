#include <iostream>
#include "InventoryScene.h"
#include "GL\glew.h"
#include "LoadTGA.h"

#include "../Application.h"
#include "GraphicsManager.h"
#include "MeshBuilder.h"
#include "RenderHelper.h"

#include "KeyboardController.h"
#include "SceneManager.h"

#include "../Animation/AnimationsContainer.h"

InventoryScene::InventoryScene()
{

}
InventoryScene::~InventoryScene()
{

}

void InventoryScene::Init()
{
	// Create and attach the camera to the scene
	camera.Init(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);

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

	item_index = 0;
	current_page = 0;
	chara_holder = nullptr;
	item_holder = nullptr;

	//Init inventory
	player_inventory = new Inventory();

	//Some items in the "Shop"
	player_inventory->AddItem(new HealthPotion());
	player_inventory->AddItem(new HealthPotion());
	player_inventory->AddItem(new MaxHealthPotion());
	player_inventory->AddItem(new HealthPotion());
	player_inventory->AddItem(new HealthPotion());
	player_inventory->AddItem(new MaxHealthPotion());
	player_inventory->AddItem(new HealthPotion());
	player_inventory->AddItem(new MaxHealthPotion());
	player_inventory->AddItem(new MaxHealthPotion());
	player_inventory->AddItem(new MaxHealthPotion());
	player_inventory->AddItem(new MaxHealthPotion());

	//Init Menus
	utilitybuttons = new Menu();
	display_inventory = new Inventory_Menu();
	character_menu = new Menu();

	//Back Button
	PreviousScene_Button* backbtn = new PreviousScene_Button();
	backbtn->SetText("Back");
	backbtn->SetTextOffset(50, 0);
	backbtn->SetScale(150, 100);
	backbtn->SetPosition(50, 1000);
	backbtn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	backbtn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	utilitybuttons->AddButton(backbtn);

	Increment_Button* nextpage = new Increment_Button();
	nextpage->SetTargetValue(current_page);
	nextpage->SetIncrementAmount(1);
	nextpage->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	nextpage->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	nextpage->SetText("Next\npage");
	nextpage->SetScale(200, 100);
	nextpage->SetPosition(700, 100);
	nextpage->SetTextOffset(60, 15);
	display_inventory->SetNextButton(nextpage);

	Increment_Button* prevpage = new Increment_Button();
	prevpage->SetTargetValue(current_page);
	prevpage->SetIncrementAmount(-1);
	prevpage->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	prevpage->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	prevpage->SetText("Previous\n  page");
	prevpage->SetScale(200, 100);
	prevpage->SetPosition(300, 100);
	prevpage->SetTextOffset(25, 15);
	display_inventory->SetPreviousButton(prevpage);

	used_item = new PopUp_Button();
	used_item->SetPosition(Application::GetInstance().GetWindowWidth() * 0.5f, Application::GetInstance().GetWindowHeight() * 0.5f);
	used_item->SetScale(800, 200);
	used_item->SetActive(false);
	used_item->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	used_item->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	used_item->SetTextOffset(120, 0);
	utilitybuttons->AddButton(used_item);

	//Make dummy party
	for (unsigned i = 0; i < 4; ++i)
	{
		CharacterInfo* charahehe = new CharacterInfo();
		charahehe->stats.AddVit(Math::RandIntMinMax(10, 200));
		charahehe->stats.AddStr(50);
		charahehe->stats.AddInt(65);
		charahehe->stats.AddMind(50);
		charahehe->stats.AddDex(40);
		charahehe->stats.AddAgi(3);
		charahehe->stats.AddLevel(5);
		charahehe->name = "Kek";
		charahehe->id = 0;
		charahehe->stats.UpdateStats();
		charahehe->HP = charahehe->stats.GetMaxHP();
		charahehe->skill_branch_index[0] = 0;
		charahehe->skill_branch_index[1] = 0;
		charahehe->skill_branch_index[2] = 0;
		charahehe->skill_branch_index[3] = 0;
		charahehe->anim.AddAnimation("walk");
		charahehe->anim.PlayAnimation("walk");
		dummy_party[i] = charahehe;
	}

	float offset_x = 1200.f;
	float offset_y = 700.f;
	for (unsigned i = 0; i < 4; ++i)
	{
		//Stop loop at the first empty slot it reaches
		if (dummy_party[i] == nullptr)
			break;

		if (i == 2)
		{
			offset_x = 1200.f;
			offset_y -= 400.f;
		}

		//Add character button for each respective character
		chara_select_btn[i] = new SelectCharacterForItem_Button();
		chara_select_btn[i]->SetActive(true);
		chara_select_btn[i]->SetPosition(offset_x, offset_y);
		chara_select_btn[i]->SetScale(350, 350);
		chara_select_btn[i]->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
		chara_select_btn[i]->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
		chara_select_btn[i]->SetCharacter(dummy_party[i]);	//TODO: Use info from player's party class
		chara_select_btn[i]->SetCharacterHolder(chara_holder);
		character_menu->AddButton(chara_select_btn[i]);

		offset_x += 425;
	}

	//Make the menu
	display_inventory->SetPlayerInventory(player_inventory);
	display_inventory->SetItemsPerPage(4);
	display_inventory->SetPosition(500, 850);
	display_inventory->SetCurrentPage(current_page);
	display_inventory->UpdateButtonPositions(item_holder);
}
void InventoryScene::Update()
{
	utilitybuttons->Update();
	display_inventory->Update();
	character_menu->Update();

	//Check for character button press
	for (unsigned i = 0; i < 4; ++i)
	{
		if (chara_select_btn[i]->m_isHovered)
			chara_select_btn[i]->UpdateAnimation();

		if (chara_select_btn[i]->m_isPressed)
			chara_holder = chara_select_btn[i]->m_chara;
	}

	//Check for item pressed
	for (unsigned i = 0; i < display_inventory->m_buttonList.size(); ++i)
	{
		if (!display_inventory->m_buttonList[i]->GetIsActive())
			continue;

		if (display_inventory->m_buttonList[i]->m_isPressed)
		{
			item_index = dynamic_cast<Inventory_Button*>(display_inventory->m_buttonList[i])->index;
			item_holder = dynamic_cast<Inventory_Button*>(display_inventory->m_buttonList[i])->m_item;
		}
	}

	//If clicked on both an item and character, use it
	if (chara_holder != nullptr && item_holder != nullptr)
	{
		used_item->SetText("Used " + player_inventory->m_inventoryList[item_index]->GetName() + " on " + chara_holder->name + "!");
		if (player_inventory->UseItem(item_index, chara_holder))
		{
			used_item->SetActive(true);
			chara_holder = nullptr;
			item_holder = nullptr;
			display_inventory->ClearButtonList();
			display_inventory->UpdateButtonPositions(item_holder);
		}
		else
		{
			used_item->SetActive(true);
			used_item->SetText("Could not use item.");
		}
	}

	if (KeyboardController::GetInstance()->IsKeyPressed(VK_ESCAPE))
		SceneManager::GetInstance()->quit = true;
}

void InventoryScene::Render()
{
	GraphicsManager::GetInstance()->AttachCamera(&camera);
	// Setup 2D pipeline then render 2D
	GraphicsManager::GetInstance()->SetOrthographicProjection(0, 
															  Application::GetInstance().GetWindowWidth(), 
															  0, 
															  Application::GetInstance().GetWindowHeight(), 
															  -10, 10);
	GraphicsManager::GetInstance()->DetachCamera();

	utilitybuttons->Render();
	display_inventory->Render();
	character_menu->Render();

	//Page
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(510, 100, 0);
	modelStack.Scale(100.f, 100.f, 1.f);
	RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("button_background"));
	modelStack.Translate(-0.45, 0, 0);
	modelStack.Scale(0.75f, 0.75f, 1.f);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), std::to_string(current_page + 1), Color(0, 1, 0));
	modelStack.PopMatrix();
}

void InventoryScene::Exit()
{
	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
}

void InventoryScene::Pause()
{
	item_index = 0;
	current_page = 0;
	chara_holder = nullptr;
	item_holder = nullptr;
	used_item->SetActive(false);
}