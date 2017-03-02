#include "CharacterProfile_Button.h"
#include "../Scenes/CharacterProfileScene.h"

CharacterProfile_Button::CharacterProfile_Button() : m_visable_skill_tree(false)
{
}

CharacterProfile_Button::~CharacterProfile_Button()
{
}

void CharacterProfile_Button::RunFunction()
{
	if (m_chara != nullptr)
		dynamic_cast<CharacterProfileScene*>(SceneManager::GetInstance()->SetActiveScene("CharacterProfileScene", true))->SetCharacter(m_chara, m_visable_skill_tree);
}

void CharacterProfile_Button::Render()
{
	if (!m_isActive)
		return;
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(m_pos_x, m_pos_y, m_priority);

	modelStack.PushMatrix();
	modelStack.Scale(m_scale_x, m_scale_y, 1);
	if (m_meshList[m_isHovered] != nullptr)
		RenderHelper::RenderMesh(m_meshList[m_isHovered]);
	modelStack.PopMatrix();

	if (m_chara == nullptr)
	{
		modelStack.PopMatrix();
		return;
	}

	modelStack.Translate(-m_scale_x * 0.5, 0, 1);

	//Name
	modelStack.Translate(0, 325, 0);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), m_chara->name, Color(1, 0, 0));
	modelStack.PopMatrix();

	//Level
	modelStack.Translate(0, -50, 0);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Level: " + std::to_string(m_chara->stats.Getlevel()), Color(1, 0, 0));
	modelStack.PopMatrix();

	//Character animation/portrait goes here
	modelStack.Translate(m_scale_x * 0.5f, -175, 0);
	modelStack.PushMatrix();
	modelStack.Scale(m_scale_x + 50, 350, 1);
	if(m_chara->anim.GetAnimatorSize())
		m_chara->anim.Render(); //TODO: Make sure the characters have animation (TO:REUBEN)
	modelStack.PopMatrix();

	//HP
	modelStack.Translate(-m_scale_x * 0.5f, -325, 0);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "HP: " + std::to_string(m_chara->HP) + "/" + std::to_string(m_chara->stats.GetMaxHP()), Color(1, 0, 0));
	modelStack.PopMatrix();

	//MP
	modelStack.Translate(0, -50, 0);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "MP: " + std::to_string(m_chara->MP) + "/" + std::to_string(m_chara->stats.GetMaxMP()), Color(1, 0, 0));
	modelStack.PopMatrix();

	//EXP
	modelStack.Translate(0, -50, 0);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "EXP: " + std::to_string(m_chara->EXP) + "/" + std::to_string(m_chara->stats.GetMaxEXP()), Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PopMatrix();

}

void SelectCharacterForItem_Button::Render()
{
	if (!m_isActive)
		return;
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(m_pos_x, m_pos_y, m_priority);

	modelStack.PushMatrix();
	modelStack.Scale(m_scale_x, m_scale_y, 1);
	if (m_meshList[m_isHovered] != nullptr)
		RenderHelper::RenderMesh(m_meshList[m_isHovered]);
	modelStack.PopMatrix();

	if (m_chara == nullptr)
	{
		modelStack.PopMatrix();
		return;
	}

	modelStack.Translate(-m_scale_x * 0.5, 0, 1);

	//Name
	modelStack.Translate(0, 150, 0);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), m_chara->name, Color(1, 0, 0));
	modelStack.PopMatrix();

	//Level
	modelStack.Translate(0, -25, 0);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Level: " + std::to_string(m_chara->stats.Getlevel()), Color(1, 0, 0));
	modelStack.PopMatrix();

	//Character animation/portrait goes here
	modelStack.Translate(m_scale_x * 0.5f, -90, 0);
	modelStack.PushMatrix();
	modelStack.Scale(175, 200, 1);
	//m_chara->anim.Render();	//TODO: make sure characters have animations
	modelStack.PopMatrix();

	//HP
	modelStack.Translate(-m_scale_x * 0.5f, -120, 0);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "HP: " + std::to_string(m_chara->HP) + "/" + std::to_string(m_chara->stats.GetMaxHP()), Color(1, 0, 0));
	modelStack.PopMatrix();

	//MP
	modelStack.Translate(0, -25, 0);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "MP: " + std::to_string(m_chara->MP) + "/" + std::to_string(m_chara->stats.GetMaxMP()), Color(1, 0, 0));
	modelStack.PopMatrix();

	//EXP
	modelStack.Translate(0, -25, 0);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "EXP: " + std::to_string(m_chara->EXP) + "/" + std::to_string(m_chara->stats.GetMaxEXP()), Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}