#include "Button.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"

Button::Button() : 
	GUIObject(),
	m_isPressed(false),
	m_isHovered(false)
{
	for (unsigned i = 0; i < NUM_IMAGES; ++i)
		m_meshList[i] = nullptr;
}

Button::Button(float pos_x, float pos_y, float scale_x, float scale_y) : 
	GUIObject()
{
	m_pos_x = pos_x;
	m_pos_y = pos_y;
	m_scale_x = scale_x;
	m_scale_y = scale_y;
	m_isHovered = false;
	m_isPressed = false;
	for (unsigned i = 0; i < NUM_IMAGES; ++i)
		m_meshList[i] = nullptr;
}

void Button::Render()
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

	if (m_text != "")
	{
		//Offset for text
		modelStack.Translate(-m_scale_x * 0.5, 0, 1);
		modelStack.Translate(m_text_offset_x, m_text_offset_y, 0);
		modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
		RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), m_text, Color(1, 0, 0));	
	}
	
	modelStack.PopMatrix();
}

void Toggle_Button::Render()
{
	if (!m_isActive)
		return;
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(m_pos_x, m_pos_y, m_priority);

	modelStack.PushMatrix();
	modelStack.Scale(m_scale_x, m_scale_y, 1);

	if (m_meshList[*m_toToggle] != nullptr)
		RenderHelper::RenderMesh(m_meshList[*m_toToggle]);

	modelStack.PopMatrix();

	if (*m_toToggle && m_text != "")
	{
		//Offset for text
		modelStack.Translate(-m_scale_x * 0.5, 0, 1);
		modelStack.Translate(m_text_offset_x, m_text_offset_y, 0);
		modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
		RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), m_text, Color(1, 0, 0));	
	}
	else if (!*m_toToggle && m_alt_text != "")
	{
		//Offset for text
		modelStack.Translate(-m_scale_x * 0.5, 0, 1);
		modelStack.Translate(m_text_offset_x, m_text_offset_y, 0);
		modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
		RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), m_alt_text, Color(1, 0, 0));	
	}

	modelStack.PopMatrix();
}

void SetBool_Button::Render()
{
	if (!m_isActive)
		return;
	Button::Render();
}

void ShopItem_Button::Render()
{
	if (!m_isActive)
		return;

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(m_pos_x, m_pos_y, m_priority);

	//Render Background image
	modelStack.Scale(m_scale_x, m_scale_y, 1);
	if (m_meshList[m_isHovered] != nullptr)
		RenderHelper::RenderMesh(m_meshList[m_isHovered]);

	//Render Item icon
	modelStack.PushMatrix();
	modelStack.Translate(-0.375f, 0, 1);
	modelStack.Scale(0.2f, 0.8f, 1);
	RenderHelper::RenderMesh(m_item->GetMesh());
	modelStack.PopMatrix();

	//Render Item Name
	modelStack.PushMatrix();
	modelStack.Translate(-0.25f, 0.3f, 1.f);
	modelStack.Scale(0.045f, 0.2f, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), m_item->GetName(), Color(1, 0, 0));
	modelStack.PopMatrix();

	//Render Item gold value
	modelStack.PushMatrix();
	modelStack.Translate(0.35f, 0.3f, 1.f);

	modelStack.PushMatrix();
	modelStack.Scale(0.045f, 0.2f, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), std::to_string(m_item->GetGoldValue()), Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-0.02f, 0.0f, 1);
	modelStack.Scale(0.045f, 0.2f, 1);
	RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Gold"));
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	//Render Item Description
	modelStack.PushMatrix();
	modelStack.Translate(-0.25f, 0.05f, 1.f);
	modelStack.Scale(0.035f, 0.15f, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), m_item->GetDescription(), Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}

void ShopCart_Button::Render()
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
	modelStack.Translate(0, 0, 0.1);

	//Render item icon
	if (m_targetInventory->m_inventoryList[m_item_index]->GetMesh())
		RenderHelper::RenderMesh(m_targetInventory->m_inventoryList[m_item_index]->GetMesh());
	modelStack.PopMatrix();

	//Offset for text
	modelStack.Translate(-m_scale_x * 0.5, 0, 1);
	modelStack.Translate(m_text_offset_x, m_text_offset_y, 0);
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), std::to_string(m_targetInventory->m_inventoryList[m_item_index]->GetGoldValue()), Color(1, 0, 0));

	modelStack.PopMatrix();
}

void Skill_Button::Render()
{
	if (!m_isActive)
		return;
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(m_pos_x, m_pos_y, m_priority);

	modelStack.PushMatrix();
	modelStack.Scale(m_scale_x, m_scale_y, 1);
	//Renders highlighted image when if skill is already learnt
	if (m_is_skill_learnt)
		RenderHelper::RenderMesh(m_meshList[m_is_skill_learnt]);
	else
	{
		if (m_meshList[m_isHovered] != nullptr)
			RenderHelper::RenderMesh(m_meshList[m_isHovered]);
	}
	
	modelStack.PopMatrix();

	if (m_text != "")
	{
		//Offset for text
		modelStack.Translate(-m_scale_x * 0.5, 0, 1);
		modelStack.Translate(m_text_offset_x, m_text_offset_y, 0);
		modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
		RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), m_skill->GetName(), Color(1, 0, 0));
	}

	modelStack.PopMatrix();
}

void Inventory_Button::Render()
{
	if (!m_isActive)
		return;

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(m_pos_x, m_pos_y, m_priority);

	//Render Background image
	modelStack.Scale(m_scale_x, m_scale_y, 1);
	if (m_meshList[m_isHovered] != nullptr)
		RenderHelper::RenderMesh(m_meshList[m_isHovered]);

	//Render Item icon
	modelStack.PushMatrix();
	modelStack.Translate(-0.375f, 0, 1);
	modelStack.Scale(0.2f, 0.8f, 1);
	if (m_item->GetMesh() != nullptr)
		RenderHelper::RenderMesh(m_item->GetMesh());
	modelStack.PopMatrix();

	//Render Item Name
	modelStack.PushMatrix();
	modelStack.Translate(-0.25f, 0.3f, 1.f);
	modelStack.Scale(0.045f, 0.2f, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), m_item->GetName(), Color(1, 0, 0));
	modelStack.PopMatrix();

	//Render Item gold value
	modelStack.PushMatrix();
	modelStack.Translate(0.35f, 0.3f, 1.f);

	modelStack.PushMatrix();
	modelStack.Scale(0.045f, 0.2f, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), std::to_string(m_item->GetGoldValue()), Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-0.02f, 0.0f, 1);
	modelStack.Scale(0.045f, 0.2f, 1);
	RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Gold"));
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	//Render Item Description
	modelStack.PushMatrix();
	modelStack.Translate(-0.25f, 0.05f, 1.f);
	modelStack.Scale(0.035f, 0.15f, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), m_item->GetDescription(), Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}

void LoadGame_Button::Render()
{
	if (!m_isActive)
		return;

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(m_pos_x, m_pos_y, 5);

	//Button itself
	modelStack.PushMatrix();
	modelStack.Scale(m_scale_x, m_scale_y, 1);
	if (m_meshList[m_isHovered] != nullptr)
		RenderHelper::RenderMesh(m_meshList[m_isHovered]);
	modelStack.PopMatrix();

	if (save_info == nullptr)	//Check if slot is empty
	{
		modelStack.PushMatrix();
		modelStack.Translate(-m_scale_x * 0.5, 0, 1);
		modelStack.Translate(m_text_offset_x, m_text_offset_y, 0);
		modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
		RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Empty Slot!", Color(1, 0, 0));
		modelStack.PopMatrix();

		modelStack.PopMatrix();
		return;
	}

	modelStack.PushMatrix(); //Character animations
	modelStack.Translate(-300, 125, 1);

	for (unsigned i = 0; i < 4; ++i)
	{
		//animation
		modelStack.Translate(0, -50, 0);
		modelStack.PushMatrix();
		if (save_info->GetParty()->GetMemberByIndex(i) != nullptr)
		{
			if (m_isHovered)
				save_info->GetParty()->GetMemberByIndex(i)->Update();

			modelStack.PushMatrix();	//For icon
			modelStack.Scale(50, 50, 1);
			if (save_info->GetParty()->GetMemberByIndex(i)->anim.GetAnimatorSize())
				save_info->GetParty()->GetMemberByIndex(i)->anim.Render();
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(50, 0, 0);
			modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
			RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), save_info->GetParty()->GetMemberByIndex(i)->name + " Lvl:" + std::to_string(save_info->GetParty()->GetMemberByIndex(i)->stats.Getlevel()), Color(1, 0, 0));
			modelStack.PopMatrix();
		}
		//If it's an empty slot in the party
		else
		{
			modelStack.PushMatrix();
			modelStack.Scale(50, 50, 1);
			RenderHelper::RenderMesh(m_meshList[false]);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(50, 0, 0);
			modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
			RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "--------------", Color(1, 0, 0));
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}

	modelStack.PopMatrix();// End of Character animations

	modelStack.PushMatrix(); //Save Info Location and gold

	modelStack.Translate(50, 50, 1);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), save_info->GetScene(), Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.Translate(0, -100, 1);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Gold:" + std::to_string(save_info->m_gold), Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PopMatrix();
}

void SaveGame_Button::Render()
{
	if (!m_isActive)
		return;

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(m_pos_x, m_pos_y, 5);

	//Button itself
	modelStack.PushMatrix();
	modelStack.Scale(m_scale_x, m_scale_y, 1);
	if (m_meshList[m_isHovered] != nullptr)
		RenderHelper::RenderMesh(m_meshList[m_isHovered]);
	modelStack.PopMatrix();

	if (save_info == nullptr)	//Check if slot is empty
	{
		modelStack.PushMatrix();
		modelStack.Translate(-m_scale_x * 0.5, 0, 1);
		modelStack.Translate(m_text_offset_x, m_text_offset_y, 0);
		modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
		RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Empty Slot!", Color(1, 0, 0));
		modelStack.PopMatrix();

		modelStack.PopMatrix();
		return;
	}

	modelStack.PushMatrix(); //Character animations
	modelStack.Translate(-300, 125, 1);

	for (unsigned i = 0; i < 4; ++i)
	{
		//animation
		modelStack.Translate(0, -50, 0);
		modelStack.PushMatrix();
		if (save_info->GetParty()->GetMemberByIndex(i) != nullptr)
		{
			if (m_isHovered)
				save_info->GetParty()->GetMemberByIndex(i)->Update();

			modelStack.PushMatrix();	//For icon
			modelStack.Scale(50, 50, 1);
			if (save_info->GetParty()->GetMemberByIndex(i)->anim.GetAnimatorSize())
				save_info->GetParty()->GetMemberByIndex(i)->anim.Render();
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(50, 0, 0);
			modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
			RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), save_info->GetParty()->GetMemberByIndex(i)->name + " Lvl:" + std::to_string(save_info->GetParty()->GetMemberByIndex(i)->stats.Getlevel()), Color(1, 0, 0));
			modelStack.PopMatrix();
		}
		//If it's an empty slot in the party
		else
		{
			modelStack.PushMatrix();
			modelStack.Scale(50, 50, 1);
			RenderHelper::RenderMesh(m_meshList[false]);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(50, 0, 0);
			modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
			RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "--------------", Color(1, 0, 0));
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}
	
	modelStack.PopMatrix();// End of Character animations

	modelStack.PushMatrix(); //Save Info Location and gold

	modelStack.Translate(50, 50, 1);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), save_info->GetScene(), Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.Translate(0, -100, 1);
	modelStack.PushMatrix();
	modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Gold:" + std::to_string(save_info->m_gold), Color(1, 0, 0));
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PopMatrix();
}