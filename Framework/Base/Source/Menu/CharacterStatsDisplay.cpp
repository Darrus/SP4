#include "CharacterStatsDisplay.h"


CharacterStats_Display::CharacterStats_Display() : m_chara(nullptr)
{
}


CharacterStats_Display::~CharacterStats_Display()
{
}

void CharacterStats_Display::Render()
{
	if (!m_isActive)
		return;

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(m_pos_x, m_pos_y, 5);

	modelStack.PushMatrix();
	modelStack.Scale(m_scale_x, m_scale_y, 1);
	RenderHelper::RenderMesh(m_image);
	modelStack.PopMatrix();

	if (m_chara == nullptr)
		return;
	
	modelStack.PushMatrix();  //Character animation/portrait goes here
	
	//animation
	modelStack.Translate(-400, 100, 1);
	modelStack.PushMatrix();
	modelStack.Scale(400, 450, 1);
	m_chara->anim.Render();
	modelStack.PopMatrix();

	//HP
	modelStack.Translate(-110, -250, 0);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "HP:" + std::to_string(m_chara->HP) + "/" + std::to_string(m_chara->stats.GetMaxHP()), Color(1, 0, 0));
	modelStack.PopMatrix();

	//MP
	modelStack.Translate(0, -50, 0);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "MP:" + std::to_string(m_chara->MP) + "/" + std::to_string(m_chara->stats.GetMaxMP()), Color(1, 0, 0));
	modelStack.PopMatrix();

	//EXP
	modelStack.Translate(0, -50, 0);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "EXP:" + std::to_string(m_chara->EXP) + "/" + std::to_string(m_chara->stats.GetMaxEXP()), Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PopMatrix();//End of character animation/portrait and stuff

	modelStack.PushMatrix();//Main stats

	//Str
	modelStack.Translate(-80, 200, 1);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "STR:" + std::to_string(m_chara->stats.GetStr()), Color(1, 0, 0));
	modelStack.PopMatrix();

	//Vit
	modelStack.Translate(0, -50, 1);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "VIT:" + std::to_string(m_chara->stats.GetVit()), Color(1, 0, 0));
	modelStack.PopMatrix();

	//Int
	modelStack.Translate(0, -50, 1);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "INT:" + std::to_string(m_chara->stats.GetInt()), Color(1, 0, 0));
	modelStack.PopMatrix();

	//Mind
	modelStack.Translate(0, -50, 1);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "MND:" + std::to_string(m_chara->stats.GetMind()), Color(1, 0, 0));
	modelStack.PopMatrix();

	//Agi
	modelStack.Translate(0, -50, 1);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "AGI:" + std::to_string(m_chara->stats.GetAgi()), Color(1, 0, 0));
	modelStack.PopMatrix();

	//Dex
	modelStack.Translate(0, -50, 1);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "DEX:" + std::to_string(m_chara->stats.GetDex()), Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PopMatrix();//End of main stats

	modelStack.PushMatrix();//Sub stats

	//Damage
	modelStack.Translate(150, 200, 1);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Damage:" + std::to_string(m_chara->stats.GetDamage()), Color(1, 0, 0));
	modelStack.PopMatrix();

	//Spell Damage
	modelStack.Translate(0, -50, 1);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Spell Damage:" + std::to_string(m_chara->stats.GetSpellDamage()), Color(1, 0, 0));
	modelStack.PopMatrix();

	//Defence
	modelStack.Translate(0, -50, 1);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Defence:" + std::to_string(m_chara->stats.GetDefence()), Color(1, 0, 0));
	modelStack.PopMatrix();

	//Dodge Rate
	modelStack.Translate(0, -50, 1);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Dodge Rate:" + std::to_string(m_chara->stats.GetDodgeRate()), Color(1, 0, 0));
	modelStack.PopMatrix();

	//Critical Rate
	modelStack.Translate(0, -50, 1);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Critical Rate:" + std::to_string(m_chara->stats.GetCritRate()), Color(1, 0, 0));
	modelStack.PopMatrix();

	//Recharge Rate
	modelStack.Translate(0, -50, 1);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Recharge Rate:" + std::to_string(m_chara->stats.GetRechargeRate()), Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PopMatrix();//End of sub stats

	modelStack.PushMatrix();//Skill Points
	modelStack.Translate(-80, -175, 1);
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Skill Points Avaliable:" + std::to_string(m_chara->stats.GetSkillPoints()), Color(1, 0, 0));
	modelStack.PopMatrix();//End of Skill Points

	modelStack.PopMatrix();//END


}