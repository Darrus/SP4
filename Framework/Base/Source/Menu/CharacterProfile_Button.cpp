#include "CharacterProfile_Button.h"


CharacterProfile_Button::CharacterProfile_Button()
{
}


CharacterProfile_Button::~CharacterProfile_Button()
{
}

void CharacterProfile_Button::Render()
{
	if (!m_isActive)
		return;
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(m_pos_x, m_pos_y, 0);

	modelStack.PushMatrix();
	modelStack.Scale(m_scale_x, m_scale_y, 1);
	if (m_meshList[m_isHovered] != nullptr)
		RenderHelper::RenderMesh(m_meshList[m_isHovered]);
	modelStack.PopMatrix();

	if (m_chara == nullptr)
		return;

	modelStack.Translate(-m_scale_x * 0.5, 0, 1);

	modelStack.Translate(0, 200, 0);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), m_chara->name, Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.Translate(0, -600, 0);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), std::to_string(m_chara->HP) + "/" + std::to_string(m_chara->stats.GetMaxHP()), Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.Translate(0, -100, 0);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), std::to_string(m_chara->MP) + "/" + std::to_string(m_chara->stats.GetMaxMP()), Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.Translate(0, -100, 0);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), std::to_string(m_chara->EXP) + "/" + std::to_string(m_chara->stats.GetMaxEXP()), Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PopMatrix();

}