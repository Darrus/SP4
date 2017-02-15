#include "Menu.h"
#include "MouseController.h"

Menu::Menu()
{
	m_mouse_x = 0.0;
	m_mouse_y = 0.0;
}


Menu::~Menu()
{
	for (unsigned i = 0; i < m_buttonList.size(); ++i)
		delete m_buttonList[i];
}

void Menu::Update()
{
	MouseController::GetInstance()->GetMousePosition(m_mouse_x, m_mouse_y);

	m_mouse_y = 1 - m_mouse_y / Application::GetInstance().GetWindowHeight();

	for (unsigned i = 0; i < m_buttonList.size(); ++i)
	{
		if (m_mouse_x / Application::GetInstance().GetWindowWidth() > m_buttonList[i]->GetScreenPositionX() - m_buttonList[i]->GetScreenScaleX() * 0.5 &&
			m_mouse_x / Application::GetInstance().GetWindowWidth() < m_buttonList[i]->GetScreenPositionX() + m_buttonList[i]->GetScreenScaleX() * 0.5 &&
			//m_mouse_y / Application::GetInstance().GetWindowHeight() > m_buttonList[i]->GetScreenPositionY() - m_buttonList[i]->GetScreenScaleY() * 0.5 &&
			//m_mouse_y / Application::GetInstance().GetWindowHeight() < m_buttonList[i]->GetScreenPositionY() + m_buttonList[i]->GetScreenScaleY() * 0.5 &&
			m_mouse_y > m_buttonList[i]->GetScreenPositionY() - m_buttonList[i]->GetScreenScaleY() * 0.5 &&
			m_mouse_y < m_buttonList[i]->GetScreenPositionY() + m_buttonList[i]->GetScreenScaleY() * 0.5 &&
			MouseController::GetInstance()->IsButtonPressed(MouseController::LMB))
			m_buttonList[i]->RunFunction();
	}
}

void Menu::Render()
{
	for (unsigned i = 0; i < m_buttonList.size(); ++i)
		m_buttonList[i]->Render();
}