#include "Button.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"

Button::Button() :
	m_pos_x(0.0f),
	m_pos_y(0.0f),
	m_scale_x(100.f),
	m_scale_y(100.f),
	m_isHovered(false),
	m_text(""),
	m_text_offset_x(0), 
	m_text_offset_y(0),
	m_text_scale_x(30),
	m_text_scale_y(30.f)
{
	for (unsigned i = 0; i < NUM_IMAGES; ++i)
		m_meshList[i] = nullptr;
}

Button::Button(float pos_x, float pos_y, float scale_x, float scale_y) : 
	m_pos_x(pos_x),
	m_pos_y(pos_y),
	m_scale_x(scale_x),
	m_scale_y(scale_y),
	m_isHovered(false),
	m_text(""),
	m_text_offset_x(0),
	m_text_offset_y(0),
	m_text_scale_x(30),
	m_text_scale_y(30.f)
{
	for (unsigned i = 0; i < NUM_IMAGES; ++i)
		m_meshList[i] = nullptr;
}

void Button::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(m_pos_x, m_pos_y, 0);

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
		RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), m_text, Color(1, 0, 0));	//NOTE::COLOUR DOESN'T WORK. THANKS ALOT, TOH.
	}
	
	modelStack.PopMatrix();
}

//void Button::Render()
//{
//
//}