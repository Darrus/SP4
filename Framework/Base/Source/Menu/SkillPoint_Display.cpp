#include "SkillPoint_Display.h"


SkillPoint_Display::SkillPoint_Display() : m_target_character(nullptr)
{
}


SkillPoint_Display::~SkillPoint_Display()
{
}

void SkillPoint_Display::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(m_pos_x, m_pos_y, 0);

	modelStack.PushMatrix();
	modelStack.Scale(m_scale_x, m_scale_y, 1);
	RenderHelper::RenderMesh(m_image);
	modelStack.PopMatrix();

	modelStack.Translate(-m_scale_x * 0.5, 0, 1);
	modelStack.Translate(m_text_offset_x, m_text_offset_y, 0);
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Skill Points:" + std::to_string(m_target_character->stats.GetSkillPoints()), Color(1, 0, 0));
	modelStack.PopMatrix();
}


void CharacterName_Display::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(m_pos_x, m_pos_y, 0);

	modelStack.PushMatrix();
	modelStack.Scale(m_scale_x, m_scale_y, 1);
	RenderHelper::RenderMesh(m_image);
	modelStack.PopMatrix();

	modelStack.Translate(-m_scale_x * 0.5, 0, 1);
	modelStack.Translate(m_text_offset_x, m_text_offset_y, 0);
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), m_target_character->name, Color(1, 0, 0));
	modelStack.PopMatrix();
}