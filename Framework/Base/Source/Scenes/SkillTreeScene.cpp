#include "SkillTreeScene.h"
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

SkillTreeScene::SkillTreeScene()
{
}

SkillTreeScene::~SkillTreeScene()
{
}

void SkillTreeScene::Init()
{
	// Create and attach the camera to the scene
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	float windowWidth = Application::GetInstance().GetWindowWidth();
	float windowHeight = Application::GetInstance().GetWindowHeight();

	MeshBuilder::GetInstance()->GenerateSpriteAnimation("Character", 4, 9);
	MeshBuilder::GetInstance()->GetMesh("Character")->textureID = LoadTGA("Image//character.tga");

	MeshBuilder::GetInstance()->GenerateQuad("button_background", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("button_background")->textureID = LoadTGA("Image//Buttons//button_background.tga");

	MeshBuilder::GetInstance()->GenerateQuad("button_background_alt", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("button_background_alt")->textureID = LoadTGA("Image//Buttons//button_background_alt.tga");

	//Skill Display
	m_display = new SkillDisplay();
	m_display->SetPosition(1450, 600);
	m_display->SetScale(800,600);
	m_display->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));

	//Initialise the Skill Container
	SkillContainer::GetInstance()->Init();

	//Add some dummy skills
	skill_branch[BRANCH_P_ATK].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_P_ATK].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_P_ATK].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_P_ATK].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_P_ATK].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_P_ATK].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));

	skill_branch[BRANCH_M_ATK].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_M_ATK].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_M_ATK].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_M_ATK].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_M_ATK].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_M_ATK].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));

	skill_branch[BRANCH_P_DEF].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_P_DEF].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_P_DEF].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_P_DEF].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_P_DEF].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_P_DEF].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));

	skill_branch[BRANCH_M_DEF].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_M_DEF].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_M_DEF].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_M_DEF].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_M_DEF].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));
	skill_branch[BRANCH_M_DEF].push_back(SkillContainer::GetInstance()->GetSkill("Heal"));

	//A dummy character for placeholder
	dummy_values();

	//Make a menu for the skill buttons
	skill_menu = new Skill_Menu();
	utility_menu = new Menu();

	//BUTTONS 
	//Back button
	PreviousScene_Button* backbtn = new PreviousScene_Button();
	backbtn->SetText("Back");
	backbtn->SetTextOffset(50, 0);
	backbtn->SetScale(150, 100);
	backbtn->SetPosition(50, 1000);
	backbtn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	backbtn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	utility_menu->AddButton(backbtn);

	//Popup button
	m_popup = new PopUp_Button();
	m_popup->SetPosition(Application::GetInstance().GetWindowWidth() * 0.5f, Application::GetInstance().GetWindowHeight() * 0.5f);
	m_popup->SetScale(800,600);
	m_popup->SetActive(false);
	m_popup->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	m_popup->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	m_popup->SetTextOffset(150, 0);
	utility_menu->AddButton(m_popup);

	//GUIObjects for utilities notifications around the screen
	GUIObject* m_skill_click_notification = new GUIObject();
	m_skill_click_notification->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	m_skill_click_notification->SetPosition(1450, 200);
	m_skill_click_notification->SetScale(700, 100);
	m_skill_click_notification->SetText("Double-click to learn a skill");
	m_skill_click_notification->SetTextOffset(70, 0);
	GUIObject_list.push_back(m_skill_click_notification);

	GUIObject* p_atk = new GUIObject();
	p_atk->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	p_atk->SetPosition(410, 890);
	p_atk->SetScale(650, 60);
	p_atk->SetText("Physical Attack Branch");
	GUIObject_list.push_back(p_atk);

	GUIObject* p_def = new GUIObject();
	p_def->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	p_def->SetPosition(410, 665);
	p_def->SetScale(650, 60);
	p_def->SetText("Physical Defense Branch");
	GUIObject_list.push_back(p_def);

	GUIObject* m_atk = new GUIObject();
	m_atk->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	m_atk->SetPosition(410, 440);
	m_atk->SetScale(650, 60);
	m_atk->SetText("Magical Attack Branch");
	GUIObject_list.push_back(m_atk);

	GUIObject* m_def = new GUIObject();
	m_def->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	m_def->SetPosition(410, 215);
	m_def->SetScale(650, 60);
	m_def->SetText("Magical Defense Branch");
	GUIObject_list.push_back(m_def);

	//Character info display stuff
	display_skill_points = new SkillPoint_Display();
	display_skill_points->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	display_skill_points->SetPosition(1800, 1000);
	display_skill_points->SetScale(350, 60);
	display_skill_points->SetText("Skill Points");
	display_skill_points->SetTargetCharacter(character);
	GUIObject_list.push_back(display_skill_points);

	display_character_name = new CharacterName_Display();
	display_character_name->SetPosition(Application::GetInstance().GetWindowWidth() * 0.5, 1050);
	display_character_name->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	display_character_name->SetScale(500, 100);
	display_character_name->SetTargetCharacter(character);
	GUIObject_list.push_back(display_character_name);


	//Init the skill buttons
	init_skills();
}

void SkillTreeScene::Update()
{
	utility_menu->Update();
	skill_menu->Update();
}

void SkillTreeScene::Render()
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
	skill_menu->Render();
	m_display->Render();

	//GUI Objects 
	for (unsigned i = 0; i < GUIObject_list.size(); ++i)
		GUIObject_list[i]->Render();
}

void SkillTreeScene::Exit()
{
	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
	delete character;
}

void SkillTreeScene::init_skills()
{
	float offset_y = 800.f;
	//Create buttons for learning the skills
	for (unsigned currentBranch = BRANCH_P_ATK; currentBranch < NUM_BRANCHES; ++currentBranch)
	{
		bool skill_learnt = true;
		//Renders current Branch
		for (unsigned index_in_branch = 0; index_in_branch < skill_branch[currentBranch].size(); ++index_in_branch)
		{
			//Rest of the skills are not yet learnt
			if (character->skill_branch_index[currentBranch] == index_in_branch)
				skill_learnt = false;

			Skill_Button* skill_btn = new Skill_Button();
			skill_btn->SetText(skill_branch[currentBranch][index_in_branch]->GetName());
			skill_btn->SetPosition(index_in_branch * 150.f + 150.f, offset_y);
			skill_btn->SetScale(125.f, 125.f);
			skill_btn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
			skill_btn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));

			//Skill pointer stuff
			skill_btn->SetIsSkillLearnt(skill_learnt);
			skill_btn->SetSkill(skill_branch[currentBranch][index_in_branch]);
			skill_btn->SetTargetDisplay(m_display);
			skill_btn->SetTargetCharacter(character);
			skill_btn->SetBranch(currentBranch);
			skill_btn->SetIndexInBranch(index_in_branch);
			skill_btn->SetPopUpButton(m_popup);
			skill_menu->AddButton(skill_btn);
		}
		offset_y -= 225.f;
	}
}

void SkillTreeScene::dummy_values()
{
	//Dummy character
	character = new CharacterInfo();
	character->skill_branch_index[BRANCH_P_ATK] = 1;
	character->skill_branch_index[BRANCH_M_ATK] = 4;
	character->skill_branch_index[BRANCH_P_DEF] = 2;
	character->skill_branch_index[BRANCH_M_DEF] = 3;
	character->stats.AddSkillPoint(3);
	character->name = "Dogshit";
}

void SkillTreeScene::SetCharacter(CharacterInfo* chara)
{
	//Set the new character
	character = chara;

	//Clear and reinitialise the skill buttons
	skill_menu->ClearButtonList();
	init_skills();

	//Update the display info stuff
	display_skill_points->SetTargetCharacter(character);
	display_character_name->SetTargetCharacter(character);
}