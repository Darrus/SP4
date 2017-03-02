#include "LoadGameScene.h"
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

LoadGameScene::LoadGameScene()
{
	load_slot[0] = nullptr;
	load_slot[1] = nullptr;
	load_slot[2] = nullptr;
}

LoadGameScene::~LoadGameScene()
{
}

void LoadGameScene::Init()
{
	// Create and attach the camera to the scene
	utility_menu = new Menu();

	ChangeScene_Button* backbtn = new ChangeScene_Button();
	backbtn->SetText("Back");
	backbtn->SetTextOffset(50, 0);
	backbtn->SetScale(150, 100);
	backbtn->SetPosition(50, 1000);
	backbtn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	backbtn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	backbtn->SetDesiredScene("MainMenuScene");
	utility_menu->AddButton(backbtn);

	int NUM_OF_SAVE_SLOTS = 3;
	for (unsigned i = 1; i < NUM_OF_SAVE_SLOTS+1; ++i)
	{
		LoadGame_Button* load_btn = new LoadGame_Button();

		load_btn->SetActive(true);
		load_btn->SetPosition(Application::GetInstance().GetWindowWidth() * 0.5f, Application::GetInstance().GetWindowHeight() - i * 300.f);
		load_btn->SetScale(700, 250);
		load_btn->SetText(std::to_string(i));
		load_btn->SetLoadSlotIndex(i);
		load_btn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
		load_btn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
		load_btn->SetTextOffset(110, 0);
		load_btn->InitialiseSaveInfo();

		//Add the button to the menu
		utility_menu->AddButton(load_btn);

		//To keep track of them
		load_slot[i - 1] = load_btn;
	}

	//Background
	background = new GUIObject();
	background->SetActive(true);
	background->SetPosition(Application::GetInstance().GetWindowWidth() * 0.5f, Application::GetInstance().GetWindowHeight() * 0.5f);
	background->SetScale(1920, 1080);
	background->SetImage(MeshBuilder::GetInstance()->GetMesh("mainmenubg"));
	background->SetTextOffset(110, 0);
	background->SetPriority(-1);
}

void LoadGameScene::Update()
{
	utility_menu->Update();
}

void LoadGameScene::Render()
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

	utility_menu->Render();
	background->Render();
}

void LoadGameScene::Exit()
{
	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();

	delete utility_menu;
}

void LoadGameScene::UnPause()
{
	int NUM_OF_SAVE_SLOTS = 3;
	for (unsigned i = 0; i < NUM_OF_SAVE_SLOTS; ++i)
	{
		load_slot[i]->InitialiseSaveInfo();
	}
}