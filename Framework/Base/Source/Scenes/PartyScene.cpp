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

	//Dummy characters
	for (unsigned i = 0; i < 0; ++i)
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
		charahehe->id = i;
		charahehe->stats.UpdateStats();
		charahehe->HP = charahehe->stats.GetMaxHP();
		charahehe->skill_branch_index[0] = 0;
		charahehe->skill_branch_index[1] = 0;
		charahehe->skill_branch_index[2] = 0;
		charahehe->skill_branch_index[3] = 0;
		charahehe->anim.AddAnimation("walk");
		charahehe->anim.PlayAnimation("walk");
		Player::GetInstance().GetParty()->AddMember(charahehe);
	}

	//Make the character buttons
	InitialiseCharacterButtons();
}

void PartyScene::Update()
{
	utility_menu->Update();

	for (unsigned i = 0; i < 4; ++i)
	{
		if (chara_btn[i]->m_isHovered && chara_btn[i]->m_chara != nullptr)
			chara_btn[i]->UpdateAnimation();
	}

	if (KeyboardController::GetInstance()->IsKeyPressed(VK_F3))
	{
		for (unsigned i = 0; i < 4; ++i)
			chara_btn[i]->SetCharacter(nullptr);
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

void PartyScene::InitialiseCharacterButtons()
{
	utility_menu->ClearButtonList();

	//A popup button for warnings
	prompt = new PopUp_Button();
	prompt->SetActive(false);
	prompt->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	prompt->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	prompt->SetScale(1000, 600);
	prompt->SetPosition(900, 540);
	utility_menu->AddButton(prompt);

	//Back button
	PreviousScene_Button* backbtn = new PreviousScene_Button();
	backbtn->SetText("Back");
	backbtn->SetTextOffset(50, 0);
	backbtn->SetScale(150, 100);
	backbtn->SetPosition(50, 1000);
	backbtn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	backbtn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	utility_menu->AddButton(backbtn);

	//Loop take makes buttons for every slot that isn't empty or if it finished the loop
	float offset_x = 375.f;
	for (unsigned i = 0; i < 4; ++i)
	{
		//Add character button for each respective character
		chara_btn[i] = new CharacterProfile_Button();
		chara_btn[i]->SetActive(true);
		chara_btn[i]->SetPosition(offset_x, 500);
		chara_btn[i]->SetScale(300, 700);
		chara_btn[i]->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
		chara_btn[i]->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));

		chara_btn[i]->SetCharacter(Player::GetInstance().GetParty()->GetMemberByIndex(i));
		chara_btn[i]->SetVisableSkillTree(true);

		//Add the button to the menu list
		utility_menu->AddButton(chara_btn[i]);

		//Add the hire button
		remove_btn[i] = new RemoveMember_Button();
		remove_btn[i]->SetActive(true);
		remove_btn[i]->SetPosition(offset_x, 100);
		remove_btn[i]->SetScale(300, 100);
		remove_btn[i]->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
		remove_btn[i]->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
		remove_btn[i]->chara_btn = chara_btn[i];
		remove_btn[i]->prompt_button = prompt;

		if (Player::GetInstance().GetParty()->GetMemberByIndex(i) == nullptr)
			remove_btn[i]->m_empty_slot = true;
		else
		{
			remove_btn[i]->m_index_in_party = i;
			remove_btn[i]->m_empty_slot = false;
			remove_btn[i]->SetTextOffset(55, 15);
			remove_btn[i]->SetText(" Abandon\nCharacter");
		}

		//Add the remove button to the menu list
		utility_menu->AddButton(remove_btn[i]);

		offset_x += 425;
	}

}

void PartyScene::UnPause()
{
	InitialiseCharacterButtons();
}