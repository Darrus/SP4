#include "SkillDisplay.h"


SkillDisplay::SkillDisplay() : m_skill(nullptr)
{
}


SkillDisplay::~SkillDisplay()
{
}

void SkillDisplay::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();

	modelStack.PushMatrix();
	modelStack.Translate(m_pos_x, m_pos_y, 0);
	modelStack.Scale(m_scale_x, m_scale_y, 1);
	RenderHelper::RenderMesh(m_image);
	modelStack.PopMatrix();

	if (m_skill == nullptr)
		return;

	string target_ally = "Target Ally :";
	if (m_skill->IsAllyTargetable())
		target_ally += "YES";
	else
		target_ally += "NO";

	string target_enemy = "Target Enemy :";
	if (m_skill->IsEnemyTargetable())
		target_enemy += "YES";
	else
		target_enemy += "NO";

	modelStack.PushMatrix();
	modelStack.Translate(m_pos_x, m_pos_y, 1);
	modelStack.Scale(m_scale_x, m_scale_y, 1);

	//Placeholder for icon
	modelStack.PushMatrix();
	modelStack.Translate(-0.35, 0.35, 0);
	modelStack.Scale(0.15, 0.2, 1);
	RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh(m_skill->GetIconName()));
	modelStack.PopMatrix();

	////////////////////////////////////////
	modelStack.PushMatrix();
	modelStack.Translate(-0.2, 0.40, 0);

	//Name 
	modelStack.PushMatrix();
	modelStack.Scale(0.075, 0.12, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), m_skill->GetName(), Color(1, 0, 0));
	modelStack.PopMatrix();

	//Mana Cost
	modelStack.Translate(0, -0.10, 0);
	modelStack.PushMatrix();
	modelStack.Scale(0.075, 0.12, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Mana Cost:" + std::to_string(m_skill->GetManaCost()), Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	////////////////////////////////////////

	modelStack.PushMatrix();
	modelStack.Translate(-0.45, 0.175, 0);

	//Target Ally? 
	modelStack.PushMatrix();
	modelStack.Scale(0.035, 0.065, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), target_ally, Color(1, 0, 0));	
	modelStack.PopMatrix();

	modelStack.Translate(0, -0.05, 0);

	//Target Enemy? 
	modelStack.PushMatrix();
	modelStack.Scale(0.035, 0.065, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), target_enemy, Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.Translate(0.5, 0.05, 0);

	//Max Targets? 
	modelStack.PushMatrix();
	modelStack.Scale(0.035, 0.065, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Max Targets :" + std::to_string(m_skill->GetMaxNumberOfTargets()), Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	////////////////////////////////////////

	//Description
	modelStack.PushMatrix();
	modelStack.Translate(-0.45, -0.035, 0);
	modelStack.Scale(0.035, 0.065, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Skill Description here.", Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}