#include "Menu.h"
#include "MouseController.h"

Menu::Menu()
{
	m_mouse_x = 0.0;
	m_mouse_y = 0.0;
}


Menu::~Menu()
{
	for (auto it = m_buttonList.begin(); it != m_buttonList.end(); ++it)
		delete *it;

	m_buttonList.clear();
}

void Menu::Update()
{
	MouseController::GetInstance()->GetMousePosition(m_mouse_x, m_mouse_y);
	m_mouse_x /= Application::GetInstance().GetWindowWidth();
	m_mouse_y = 1 - m_mouse_y / Application::GetInstance().GetWindowHeight();	//Invert the mouse_y 

	for (unsigned i = 0; i < m_buttonList.size(); ++i)
	{
		if (checkForHover(m_buttonList[i]))
		{
			m_buttonList[i]->m_isHovered = true;

			if (MouseController::GetInstance()->IsButtonReleased(MouseController::LMB))
				m_buttonList[i]->RunFunction();

			break;	//you don't hover over more than one button at a time so we can break here
		}
		else
			m_buttonList[i]->m_isHovered = false;
	}
}

void Menu::Render()
{
	for (unsigned i = 0; i < m_buttonList.size(); ++i)
		m_buttonList[i]->Render();
}

bool Menu::checkForHover(Button* btn)
{
	if (m_mouse_x > btn->GetScreenPositionX() - btn->GetScreenScaleX() * 0.5 &&
		m_mouse_x < btn->GetScreenPositionX() + btn->GetScreenScaleX() * 0.5 &&
		//m_mouse_y / Application::GetInstance().GetWindowHeight() > btn->GetScreenPositionY() - btn->GetScreenScaleY() * 0.5 &&
		//m_mouse_y / Application::GetInstance().GetWindowHeight() < btn->GetScreenPositionY() + btn->GetScreenScaleY() * 0.5 &&
		m_mouse_y > btn->GetScreenPositionY() - btn->GetScreenScaleY() * 0.5 &&
		m_mouse_y < btn->GetScreenPositionY() + btn->GetScreenScaleY() * 0.5)
		return true;
	else
		return false;
}