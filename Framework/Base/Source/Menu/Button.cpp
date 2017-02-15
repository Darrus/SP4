#include "Button.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"

Button::Button() :
	m_pos_x(0.0f),
	m_pos_y(0.0f),
	m_scale_x(1.0f),
	m_scale_y(1.0f),
	m_function(nullptr)
{

}

Button::Button(FunctionPointer functionToRun)	:
	m_pos_x(0.0f),
	m_pos_y(0.0f),
	m_scale_x(1.0f),
	m_scale_y(1.0f),
	m_function(functionToRun)
{
}

Button::Button(float pos_x, float pos_y, float scale_x, float scale_y, FunctionPointer &functionToRun)	:
	m_pos_x(pos_x),
	m_pos_y(pos_y),
	m_scale_x(scale_x),
	m_scale_y(scale_y),
	m_function(functionToRun)
{
}

Button::~Button()
{
}

void Button::RunFunction()
{
	m_function();
}

void Button::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(m_pos_x, m_pos_y, 0);
	modelStack.Scale(m_scale_x, m_scale_y, 1);
	
	//if (m_isHovered)
		RenderHelper::RenderMesh(m_meshList[NORMAL_IMAGE]);
	//else
		//RenderHelper::RenderMesh(m_meshList[HIGHLIGHTED_IMAGE]);

	if (m_text != "")
		RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), m_text,Color(1, 1, 1));

	modelStack.PopMatrix();
}