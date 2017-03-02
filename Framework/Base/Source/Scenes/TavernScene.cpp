#include "TavernScene.h"

// Graphics
#include "GL\glew.h"
#include "LoadTGA.h"
#include "GraphicsManager.h"

// Utilities
#include "../Application.h"
#include "KeyboardController.h"
#include "SceneManager.h"
#include "../Character/CharacterFactory.h"

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
	/*delete utility_menu;
	delete prompt;
	delete gold_display;
	delete tavern_display;
	for (int i = 0; i < 4; ++i)
	{
		if (hire_btn[i])
			delete hire_btn[i];
		if (chara_btn[i])
			delete chara_btn[i];
	}*/
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
	prompt->SetTextOffset(200, 0);
	utility_menu->AddButton(prompt);

	//TODO: Generate the random characters here
	//Dummy characters
	for (unsigned i = 0; i < 4; ++i)
	{
		tavern_slots[i] = CharacterFactory::GetInstance()->CreateCharacter();
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
	tavern_display->SetScale(350, 100);
	tavern_display->SetText("Tavern");
	tavern_display->SetTextOffset(100, 0);

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
		hire_btn[i]->SetCharacterToAdd(chara_btn[i]);
		hire_btn[i]->SetGoldCost(tavern_slots[i]->stats.Getlevel() * Math::RandIntMinMax(250, 500));
		hire_btn[i]->SetPopUp(prompt);

		//Add the button to the menu list
		utility_menu->AddButton(hire_btn[i]);

		offset_x += 425;
	}

	MeshBuilder::GetInstance()->GenerateQuad("tavern_bg", Color(1, 1, 1), 1)->textureID = LoadTGA("Image//tavern_bg.tga");

	background = new GUIObject();
	background->SetActive(true);
	background->SetPosition(Application::GetInstance().GetWindowWidth() * 0.5f, Application::GetInstance().GetWindowHeight() * 0.5f);
	background->SetScale(Application::GetInstance().GetWindowWidth(), Application::GetInstance().GetWindowHeight());
	background->SetImage(MeshBuilder::GetInstance()->GetMesh("tavern_bg"));
	background->SetPriority(-1);
}

void TavernScene::Update()
{
	utility_menu->Update();

	for (unsigned i = 0; i < 4; ++i)
	{
		if (chara_btn[i]->m_chara != nullptr && chara_btn[i]->m_isHovered)
			chara_btn[i]->UpdateAnimation();

		if (hire_btn[i]->m_isPressed && hire_btn[i]->GetCharacterToAdd() != nullptr)
		{
			gold_display->SetText("Your Gold:" + std::to_string(Player::GetInstance().m_gold));
		}
	}
}

void TavernScene::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GraphicsManager::GetInstance()->SetOrthographicProjection(0, Application::GetInstance().GetWindowWidth(), 0, Application::GetInstance().GetWindowHeight(), -10, 10);

	utility_menu->Render();
	gold_display->Render();
	tavern_display->Render();
	background->Render();
}

void TavernScene::Exit()
{
}

CharacterInfo* TavernScene::generate_random_character()
{
	//Generate Level and auto update the stats
	CharacterInfo* chara = CharacterFactory::GetInstance()->CreateCharacter();
	return chara;
}

void TavernScene::UnPause()
{
	//Generate random characters in the tavern slot 
	for (unsigned i = 0; i < 4; ++i)
	{
		tavern_slots[i] = CharacterFactory::GetInstance()->CreateCharacter();
		chara_btn[i]->m_chara = tavern_slots[i];
		hire_btn[i]->SetCharacterToAdd(chara_btn[i]);
		hire_btn[i]->SetGoldCost(tavern_slots[i]->stats.Getlevel() * Math::RandIntMinMax(250, 500));
	}
	gold_display->SetText("Your Gold:" + std::to_string(Player::GetInstance().m_gold));
}

void TavernScene::Pause()
{
	//delete the generated characters from this session
	for (unsigned i = 0; i < 4; ++i)
	{
		if (chara_btn[i]->m_chara != nullptr)
		{
			delete chara_btn[i]->m_chara;
			chara_btn[i]->m_chara = nullptr;
		}
	}
}