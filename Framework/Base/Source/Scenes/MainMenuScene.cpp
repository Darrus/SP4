#include "MainMenuScene.h"
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

MainMenuScene::MainMenuScene()
{
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::Init()
{
	SoundEngine::GetInstance()->AddRepeatSound("Prelude", "Sound/Prelude.mp3");
	// Create and attach the camera to the scene
	utility_menu = new Menu();

	NewGame_Button* new_game = new NewGame_Button();
	new_game->SetActive(true);
	new_game->SetPosition(Application::GetInstance().GetWindowWidth() * 0.5f, Application::GetInstance().GetWindowHeight() * 0.5f - 100.f);
	new_game->SetScale(400, 100);
	new_game->SetText("New Game");
	new_game->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	new_game->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	new_game->SetTextOffset(110, 0);
	new_game->SetDesiredScene("Overworld");//<- TODO: something as "new game". Maybe enable the collider box in over world of something.
	new_game->SetIsOverlay(false);
	utility_menu->AddButton(new_game);

	ChangeScene_Button* load_game = new ChangeScene_Button();
	load_game->SetActive(true);
	load_game->SetPosition(Application::GetInstance().GetWindowWidth() * 0.5f, Application::GetInstance().GetWindowHeight() * 0.5f - 250.f);
	load_game->SetScale(400, 100);
	load_game->SetText("Load Game");
	load_game->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	load_game->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	load_game->SetTextOffset(110, 0);
	load_game->SetDesiredScene("LoadGameScene");
	load_game->SetIsOverlay(false);
	utility_menu->AddButton(load_game);

	ExitGame_Button* exit_game = new ExitGame_Button();
	exit_game->SetActive(true);
	exit_game->SetPosition(Application::GetInstance().GetWindowWidth() * 0.5f, Application::GetInstance().GetWindowHeight() * 0.5f - 400.f);
	exit_game->SetScale(400, 100);
	exit_game->SetText("Exit Game");
	exit_game->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	exit_game->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	exit_game->SetTextOffset(110, 0);
	utility_menu->AddButton(exit_game);

	MeshBuilder::GetInstance()->GenerateQuad("mainmenubg", Color(1,1,1))->textureID = LoadTGA("Image//mainmenu.tga");
	//Background
	background = new GUIObject();
	background->SetActive(true);
	background->SetPosition(Application::GetInstance().GetWindowWidth() * 0.5f, Application::GetInstance().GetWindowHeight() * 0.5f);
	background->SetScale(Application::GetInstance().GetWindowWidth(), Application::GetInstance().GetWindowHeight());
	background->SetImage(MeshBuilder::GetInstance()->GetMesh("mainmenubg"));
	background->SetTextOffset(110, 0);
	background->SetPriority(-1);
}

void MainMenuScene::Update()
{
	utility_menu->Update();
}

void MainMenuScene::Render()
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

void MainMenuScene::UnPause()
{
	SoundEngine::GetInstance()->Play("Prelude");
}

void MainMenuScene::Exit()
{
	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
	delete background;
	delete utility_menu;
}