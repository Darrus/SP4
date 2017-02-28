#include "CharacterProfileScene.h"

// Graphics
#include "GL\glew.h"
#include "LoadTGA.h"
#include "GraphicsManager.h"

// Utilities
#include "../Application.h"
#include "KeyboardController.h"
#include "SceneManager.h"
#include "../Scenes/SkillTreeScene.h"

CharacterProfileScene::CharacterProfileScene() : current_character(nullptr)
{
}


CharacterProfileScene::~CharacterProfileScene()
{
}

void CharacterProfileScene::Init()
{
	SetInit(true);

	//Initialise Menu
	utility_menu = new Menu();

	//dummy character
	CharacterInfo* dummy_character = new CharacterInfo();
	dummy_character->stats.AddVit(Math::RandIntMinMax(10, 200));
	dummy_character->stats.AddStr(50);
	dummy_character->stats.AddInt(65);
	dummy_character->stats.AddMind(50);
	dummy_character->stats.AddDex(40);
	dummy_character->stats.AddAgi(3);
	dummy_character->stats.AddLevel(5);
	dummy_character->name = "cuntonio";
	dummy_character->id = 0;
	dummy_character->stats.UpdateStats();
	dummy_character->HP = dummy_character->stats.GetMaxHP();
	dummy_character->skill_branch_index[0] = 0;
	dummy_character->skill_branch_index[1] = 0;
	dummy_character->skill_branch_index[2] = 0;
	dummy_character->skill_branch_index[3] = 0;
	dummy_character->anim.AddAnimation("walk");
	dummy_character->anim.PlayAnimation("walk");

	current_character = dummy_character;

	//Back button
	PreviousScene_Button* backbtn = new PreviousScene_Button();
	backbtn->SetText("Back");
	backbtn->SetTextOffset(50, 0);
	backbtn->SetScale(150, 100);
	backbtn->SetPosition(50, 1000);
	backbtn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	backbtn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	utility_menu->AddButton(backbtn);

	//GUIObjects
	m_header_text = new GUIObject();
	m_header_text->SetPosition(Application::GetInstance().GetWindowWidth() * 0.5, 1050);
	m_header_text->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	m_header_text->SetScale(500, 100);
	m_header_text->SetTextOffset(180, 0);
	m_header_text->SetText("Party");

	// Displays character stats
	m_chara_stats = new CharacterStats_Display();
	m_chara_stats->SetPosition(Application::GetInstance().GetWindowWidth() * 0.5, Application::GetInstance().GetWindowHeight() * 0.5);
	m_chara_stats->SetImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	m_chara_stats->SetScale(1400, 700);
	m_chara_stats->SetTargetCharacter(dummy_character);

	//Button that brings player to the Skill Tree Scene
	goto_skill_tree_scene_btn = new ChangeScene_Button();
	goto_skill_tree_scene_btn->SetPosition(1125, 300);
	goto_skill_tree_scene_btn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	goto_skill_tree_scene_btn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	goto_skill_tree_scene_btn->SetText("Go To Skill Tree");
	goto_skill_tree_scene_btn->SetScale(475, 75);
	goto_skill_tree_scene_btn->SetDesiredScene("SkillTreeScene");
	goto_skill_tree_scene_btn->SetIsOverlay(true);
	utility_menu->AddButton(goto_skill_tree_scene_btn);
}

void CharacterProfileScene::Update()
{
	utility_menu->Update();
	m_chara_stats->UpdateAnimation();

	if (goto_skill_tree_scene_btn->m_isPressed)
		dynamic_cast<SkillTreeScene*>(SceneManager::GetInstance()->GetScene("SkillTreeScene"))->SetCharacter(current_character);
}

void CharacterProfileScene::Render()
{
	GraphicsManager::GetInstance()->SetOrthographicProjection(0, Application::GetInstance().GetWindowWidth(), 0, Application::GetInstance().GetWindowHeight(), -10, 10);

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(0,0,1);
	m_chara_stats->Render();
	modelStack.Translate(0, 0, 4);
	utility_menu->Render();
	modelStack.PopMatrix();
}

void CharacterProfileScene::Exit()
{
}
