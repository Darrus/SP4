#include "PartyScene.h"

// Graphics
#include "GL\glew.h"
#include "LoadTGA.h"
#include "GraphicsManager.h"

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
	back_btn->SetText("Back");
	back_btn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	back_btn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	back_btn->SetTextOffset(130, 0);

	utility_menu->AddButton(back_btn);

	//Dummy character
	CharacterInfo* charahehe = new CharacterInfo();
	charahehe->stats.AddVit(50);
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
	chara_info[0] = charahehe;

	//Chara button
	chara_btn[0] = new CharacterProfile_Button();
	chara_btn[0]->SetActive(true);
	chara_btn[0]->SetPosition(600, 500);
	chara_btn[0]->SetScale(300, 700);
	chara_btn[0]->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	chara_btn[0]->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));

	chara_btn[0]->SetCharacter(chara_info[0]);
	utility_menu->AddButton(chara_btn[0]);
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
