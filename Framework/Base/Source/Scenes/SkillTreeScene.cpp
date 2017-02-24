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

#include "../Entity/EntityFactory.h"

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

	MeshBuilder::GetInstance()->GenerateText("text", 16, 16);
	MeshBuilder::GetInstance()->GetMesh("text")->textureID = LoadTGA("Image//calibri.tga");
	MeshBuilder::GetInstance()->GetMesh("text")->material.kAmbient.Set(1, 0, 0);

	float windowWidth = Application::GetInstance().GetWindowWidth();
	float windowHeight = Application::GetInstance().GetWindowHeight();

	MeshBuilder::GetInstance()->GenerateSpriteAnimation("Character", 4, 9);
	MeshBuilder::GetInstance()->GetMesh("Character")->textureID = LoadTGA("Image//character.tga");

	MeshBuilder::GetInstance()->GenerateQuad("button_background", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("button_background")->textureID = LoadTGA("Image//Buttons//button_background.tga");

	MeshBuilder::GetInstance()->GenerateQuad("button_background_alt", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("button_background_alt")->textureID = LoadTGA("Image//Buttons//button_background_alt.tga");

	//Make a menu for the skill buttons
	skill_menu = new Menu();
	dummy_values();

	SkillContainer::GetInstance()->Init();
	init_skills();
}

void SkillTreeScene::Update()
{
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

	//character->skills.push_back();
	//glBlendFunc(1.5, 1);
	skill_menu->Render();
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
			skill_btn->SetText(std::to_string(index_in_branch));
			skill_btn->SetPosition(index_in_branch * 110.f + 50.f, offset_y);
			skill_btn->SetScale(100.f, 100.f);
			skill_btn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
			skill_btn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));

			//Skill pointer stuff
			skill_btn->SetIsSkillLearnt(skill_learnt);
			skill_btn->SetIndexInBranch(index_in_branch);
			skill_btn->SetBranch(currentBranch);
			skill_btn->SetTargetCharacter(*character);
			skill_btn->SetSkillName("Heal");

			skill_menu->AddButton(skill_btn);
		}

		offset_y -= 120.f;

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
}