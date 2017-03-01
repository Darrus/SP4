#include "TavernScene.h"

// Graphics
#include "GL\glew.h"
#include "LoadTGA.h"
#include "GraphicsManager.h"

// Utilities
#include "../Application.h"
#include "KeyboardController.h"
#include "SceneManager.h"

TavernScene::TavernScene()
{
	//Initialise as nullptrs
	tavern_slots[0] = nullptr;
	tavern_slots[1] = nullptr;
	tavern_slots[2] = nullptr;
	tavern_slots[3] = nullptr;
}


TavernScene::~TavernScene()
{
}

void TavernScene::Init()
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

	//Prompt Button
	prompt = new PopUp_Button();
	prompt->SetActive(false);
	prompt->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	prompt->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	prompt->SetScale(1000, 600);
	prompt->SetPosition(900, 540);
	utility_menu->AddButton(prompt);

	//TODO: Generate the random characters here
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
		charahehe->name = "asdasd";
		charahehe->id = 0;
		charahehe->stats.UpdateStats();
		charahehe->HP = charahehe->stats.GetMaxHP();
		charahehe->skill_branch_index[0] = 0;
		charahehe->skill_branch_index[1] = 0;
		charahehe->skill_branch_index[2] = 0;
		charahehe->skill_branch_index[3] = 0;
		charahehe->anim.AddAnimation("walk");
		charahehe->anim.PlayAnimation("walk");
		tavern_slots[i] = charahehe;
	}

	//Displays the amount of gold the player has
	gold_display = new GUIObject();
	gold_display->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	gold_display->SetPosition(1750, 1000);
	gold_display->SetScale(350, 60);
	gold_display->SetText("Your Gold:" + std::to_string(Player::GetInstance().m_gold));

	tavern_display = new GUIObject();
	tavern_display->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	tavern_display->SetPosition(Application::GetInstance().GetWindowWidth() * 0.5f + 10.f , 1000);
	tavern_display->SetScale(350, 60);
	tavern_display->SetText("Tavern");

	//Loop take makes buttons for every slot that isn't empty or if it finished the loop
	float offset_x = 375.f;
	for (unsigned i = 0; i < 4; ++i)
	{
		//Stop loop at the first empty slot it reaches
		if (tavern_slots[i] == nullptr)
			continue;

		//Add character button for each respective character
		chara_btn[i] = new CharacterProfile_Button();
		chara_btn[i]->SetActive(true);
		chara_btn[i]->SetPosition(offset_x, 500);
		chara_btn[i]->SetScale(300, 700);
		chara_btn[i]->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
		chara_btn[i]->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
		chara_btn[i]->SetCharacter(tavern_slots[i]);
		chara_btn[i]->SetVisableSkillTree(false);

		//Add the button to the menu list
		utility_menu->AddButton(chara_btn[i]);

		//Add the hire button
		hire_btn[i] = new Hire_Button();
		hire_btn[i]->SetActive(true);
		hire_btn[i]->SetPosition(offset_x, 100);
		hire_btn[i]->SetScale(300, 100);
		hire_btn[i]->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
		hire_btn[i]->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
		hire_btn[i]->SetCharacterToAdd(tavern_slots[i]);
		hire_btn[i]->SetGoldCost(10);

		//Add the button to the menu list
		utility_menu->AddButton(hire_btn[i]);

		offset_x += 425;
	}
}

void TavernScene::Update()
{
	utility_menu->Update();

	for (unsigned i = 0; i < 4; ++i)
	{
		if (chara_btn[i]->m_chara != nullptr && chara_btn[i]->m_isHovered)
			chara_btn[i]->UpdateAnimation();

		if (hire_btn[i]->m_isPressed && hire_btn[i]->m_chara_to_add)
		{
			//if full party
			if (Player::GetInstance().GetInstance().GetParty()->memberCount() == Player::GetInstance().GetInstance().GetParty()->GetMaxPartySize())
			{
				prompt->SetActive(true);
				prompt->SetText("Your Party is full!");
			}
			//If not enough gold
			else if (Player::GetInstance().m_gold < hire_btn[i]->m_gold_cost)
			{
				prompt->SetActive(true);
				prompt->SetText("You do not have enough gold!");
			}
			else
			{
				prompt->SetActive(true);
				prompt->SetText(chara_btn[i]->m_chara->name + " has joined the party!");
				chara_btn[i]->SetCharacter(nullptr);
				hire_btn[i]->SetCharacterToAdd(nullptr);
				hire_btn[i]->SetText("Nobody Here");
				gold_display->SetText("Your Gold:" + std::to_string(Player::GetInstance().m_gold));
			}
		}
	}
}

void TavernScene::Render()
{
	GraphicsManager::GetInstance()->SetOrthographicProjection(0, Application::GetInstance().GetWindowWidth(), 0, Application::GetInstance().GetWindowHeight(), -10, 10);

	utility_menu->Render();
	gold_display->Render();
	tavern_display->Render();
}

void TavernScene::Exit()
{
}

CharacterInfo* TavernScene::generate_random_character()
{
	//Generate Level and auto update the stats
	CharacterInfo* chara = new CharacterInfo();

	return chara;
}

void TavernScene::UnPause()
{
	//TODO:
	//Generate random characters in the tavern slot 

	gold_display->SetText("Your Gold:" + std::to_string(Player::GetInstance().m_gold));
}

void TavernScene::Pause()
{
	//delete the generated characters from this session
	for (unsigned i = 0; i < 4; ++i)
	{
		if (chara_btn[i]->m_chara != nullptr)
			delete chara_btn[i];
	}
}