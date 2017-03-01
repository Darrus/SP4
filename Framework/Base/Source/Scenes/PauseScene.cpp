#include "PauseScene.h"

// Graphics
#include "GL\glew.h"
#include "LoadTGA.h"
#include "GraphicsManager.h"
#include "Mesh.h"
#include "MeshBuilder.h"

// Utilities
#include "../Application.h"
#include "KeyboardController.h"
#include "SceneManager.h"

PauseScene::PauseScene()
{
}


PauseScene::~PauseScene()
{
}

void PauseScene::Init()
{
	SetInit(false);

	pause_menu = new Menu();

	PreviousScene_Button* unpause_btn = new PreviousScene_Button();
	unpause_btn->SetActive(true);
	unpause_btn->SetPosition(400, 1000);
	unpause_btn->SetScale(390, 100);
	unpause_btn->SetText("Resume");
	unpause_btn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	unpause_btn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	unpause_btn->SetTextOffset(130, 0);

	ChangeScene_Button* inventory_btn = new ChangeScene_Button();
	inventory_btn->SetPosition(800, 1000);
	inventory_btn->SetScale(390, 100);
	inventory_btn->SetText("Inventory");
	inventory_btn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	inventory_btn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	inventory_btn->SetDesiredScene("InventoryScene");
	inventory_btn->SetIsOverlay(true);
	inventory_btn->SetTextOffset(100, 0);

	ChangeScene_Button* party_btn = new ChangeScene_Button();
	party_btn->SetPosition(1200, 1000);
	party_btn->SetScale(390, 100);
	party_btn->SetText("Party");
	party_btn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	party_btn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	party_btn->SetDesiredScene("PartyScene");
	party_btn->SetIsOverlay(true);
	party_btn->SetTextOffset(135, 0);

	ChangeScene_Button* back_to_main_menu_btn = new ChangeScene_Button();
	back_to_main_menu_btn->SetPosition(1600, 1000);
	back_to_main_menu_btn->SetScale(390, 100);
	back_to_main_menu_btn->SetText("Return to\nMain Menu");
	back_to_main_menu_btn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	back_to_main_menu_btn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));;
	back_to_main_menu_btn->SetDesiredScene("MainMenuScene");
	back_to_main_menu_btn->SetIsOverlay(false);
	back_to_main_menu_btn->SetTextOffset(100,15);

	pause_menu->AddButton(unpause_btn);
	pause_menu->AddButton(inventory_btn);
	pause_menu->AddButton(party_btn);
	pause_menu->AddButton(back_to_main_menu_btn);
}

void PauseScene::Update()
{
	pause_menu->Update();
}

void PauseScene::Render()
{
	GraphicsManager::GetInstance()->SetOrthographicProjection(0, Application::GetInstance().GetWindowWidth(), 0, Application::GetInstance().GetWindowHeight(), -10, 10);

	pause_menu->Render();
}

void PauseScene::Exit()
{
}
