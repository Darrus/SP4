#include "PartyScene.h"

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

PartyScene::PartyScene()
{
}


PartyScene::~PartyScene()
{
}

void PartyScene::Init()
{
	SetInit(true);

	utility_menu = new Menu();

	back_btn = new PreviousScene_Button();
	back_btn->SetActive(true);
	back_btn->SetPosition(400, 1000);
	back_btn->SetScale(390, 100);
	back_btn->SetText("Resume");
	back_btn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	back_btn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	back_btn->SetTextOffset(130, 0);

	utility_menu->AddButton(back_btn);
}

void PartyScene::Update()
{
	utility_menu->Update();
}

void PartyScene::Render()
{
	GraphicsManager::GetInstance()->SetOrthographicProjection(0, Application::GetInstance().GetWindowWidth(), 0, Application::GetInstance().GetWindowHeight(), -10, 10);

	utility_menu->Render();
}

void PartyScene::Exit()
{
}
