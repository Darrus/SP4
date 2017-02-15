#include "Menu.h"


Menu::Menu()
{
	m_windowWidth = Application::GetInstance().GetWindowWidth();
	m_windowHeight = Application::GetInstance().GetWindowHeight();
}


Menu::~Menu()
{

}

void Menu::Update()
{
	//Check if mouse is hovering over buttons
}

void Menu::Render()
{
	for (unsigned i = 0; i < m_buttonList.size(); ++i)
	{
		m_buttonList[i]->Render();
	}
}