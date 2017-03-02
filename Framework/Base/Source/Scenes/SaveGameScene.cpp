#include "SaveGameScene.h"
#include <iostream>
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

using namespace std;

SaveGameScene::SaveGameScene()
{
	save_slots_btn[0] = nullptr;
	save_slots_btn[1] = nullptr;
	save_slots_btn[2] = nullptr;
}

SaveGameScene::~SaveGameScene()
{
}

void SaveGameScene::Init()
{
	// Create and attach the camera to the scene
	utility_menu = new Menu();

	PreviousScene_Button* backbtn = new PreviousScene_Button();
	backbtn->SetText("Back");
	backbtn->SetTextOffset(50, 0);
	backbtn->SetScale(150, 100);
	backbtn->SetPosition(50, 1000);
	backbtn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	backbtn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	utility_menu->AddButton(backbtn);

	PopUp_Button* prompt= new PopUp_Button();
	prompt->SetPosition(Application::GetInstance().GetWindowWidth() * 0.5f, Application::GetInstance().GetWindowHeight() * 0.5f);
	prompt->SetScale(800, 200);
	prompt->SetActive(false);
	prompt->SetText("Game Saved!");
	prompt->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	prompt->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	prompt->SetTextOffset(120, 0);
	utility_menu->AddButton(prompt);

	int NUM_OF_SAVE_SLOTS = 3;
	for (unsigned i = 1; i < NUM_OF_SAVE_SLOTS+1; ++i)
	{
		SaveGame_Button* save_btn = new SaveGame_Button();

		save_btn->SetActive(true);
		save_btn->SetPosition(Application::GetInstance().GetWindowWidth() * 0.5f, Application::GetInstance().GetWindowHeight() - i * 300.f);
		save_btn->SetScale(700, 250);
		save_btn->SetSaveSlotIndex(i);
		save_btn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
		save_btn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
		save_btn->SetTextOffset(130, 0);
		save_btn->m_popup = prompt;
		save_btn->InitialiseSaveInfo();

		//Add them to the menu
		utility_menu->AddButton(save_btn);

		//To keep track
		save_slots_btn[i-1] = save_btn;
	}
}

void SaveGameScene::Update()
{
	utility_menu->Update();
}

void SaveGameScene::Render()
{
	GraphicsManager::GetInstance()->AttachCamera(&camera);
	// Setup 2D pipeline then render 2D
	GraphicsManager::GetInstance()->SetOrthographicProjection(0,
		Application::GetInstance().GetWindowWidth(),
		0,
		Application::GetInstance().GetWindowHeight(),
		-10, 10);
	GraphicsManager::GetInstance()->DetachCamera();

	utility_menu->Render();
}

void SaveGameScene::Exit()
{
	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();

	delete utility_menu;
}

void SaveGameScene::UnPause()
{
	int NUM_OF_SAVE_SLOTS = 3;
	for (unsigned i = 0; i < NUM_OF_SAVE_SLOTS; ++i)
	{
		save_slots_btn[i]->InitialiseSaveInfo();
	}
}