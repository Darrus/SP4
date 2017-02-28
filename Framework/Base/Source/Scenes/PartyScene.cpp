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
	//Initialise as nullptrs
	chara_info[0] = nullptr;
	chara_info[1] = nullptr;
	chara_info[2] = nullptr;
	chara_info[3] = nullptr;
}


PartyScene::~PartyScene()
{
}

void PartyScene::Init()
{
	SetInit(true);

	utility_menu = new Menu();

	//Back button
	PreviousScene_Button* backbtn = new PreviousScene_Button();
	backbtn->SetText("Back");
	backbtn->SetTextOffset(50, 0);
	backbtn->SetScale(150, 100);
	backbtn->SetPosition(50, 1000);
	backbtn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	backbtn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	utility_menu->AddButton(backbtn);

	//Dummy characters
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
		chara_info[i] = charahehe;
	}

	//Loop take makes buttons for every slot that isn't empty or if it finished the loop
	float offset_x = 375.f;
	for (unsigned i = 0; i < 4; ++i)
	{
		//Stop loop at the first empty slot it reaches
		if (chara_info[i] == nullptr)
			break;

		//Add character button for each respective character
		chara_btn[i] = new CharacterProfile_Button();
		chara_btn[i]->SetActive(true);
		chara_btn[i]->SetPosition(offset_x, 500);
		chara_btn[i]->SetScale(300, 700);
		chara_btn[i]->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
		chara_btn[i]->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
		chara_btn[i]->SetCharacter(chara_info[i]);

		//Add the button to the menu list
		utility_menu->AddButton(chara_btn[i]);
		offset_x += 425;
	}
}

void PartyScene::Update()
{
	utility_menu->Update();

	for (unsigned i = 0; i < 4; ++i)
	{
		if (chara_btn[i]->m_isHovered)
			chara_btn[i]->UpdateAnimation();
	}
}

void PartyScene::Render()
{
	GraphicsManager::GetInstance()->SetOrthographicProjection(0, Application::GetInstance().GetWindowWidth(), 0, Application::GetInstance().GetWindowHeight(), -10, 10);

	utility_menu->Render();
}

void PartyScene::Exit()
{
}
