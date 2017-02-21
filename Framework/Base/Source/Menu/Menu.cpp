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
		if (!m_buttonList[i]->GetIsActive())
			continue;

		if (checkForHover(m_buttonList[i]))
		{
			m_buttonList[i]->m_isHovered = true;

			if (MouseController::GetInstance()->IsButtonReleased(MouseController::LMB))
				m_buttonList[i]->RunFunction();

			//break;	//you don't hover over more than one button at a time so we can break here
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

void Shop_Menu::Update()
{
	std::cout << (m_buttonList.size() / m_num_item_per_page) << std::endl;
	Menu::Update();
	//Loops back to start or end when out of bounds
	//Check if it's perfect pages
	if (m_buttonList.size() % m_num_item_per_page)
	{
		//when back from 0
		if (*m_current_page < 0)
			*m_current_page = (m_buttonList.size() / m_num_item_per_page);

		//when past max tab
		if (*m_current_page > m_buttonList.size() / m_num_item_per_page)
			*m_current_page = 0;
	}
	else
	{
		//when back from 0
		if (*m_current_page < 0)
			*m_current_page = (m_buttonList.size() / m_num_item_per_page) - 1;
		//when past max tab
		else if (*m_current_page >= m_buttonList.size() / m_num_item_per_page)
			*m_current_page = 0;
	}

	//Set all buttons to inactive first
	for (unsigned i = 0; i < m_buttonList.size(); ++i)
		m_buttonList[i]->SetActive(false);

	//If all items can be fit in one page
	if (m_buttonList.size() / m_num_item_per_page == 0)
	{
		for (unsigned i = 0; i < m_buttonList.size(); ++i)
			m_buttonList[i]->SetActive(true);
	}
	else
	{
		//If current page has more items than what the list is holding
		if ((*m_current_page + 1) * m_num_item_per_page > m_buttonList.size())
		{
			//Renders "leftovers"
			for (unsigned i = *m_current_page * m_num_item_per_page; i < m_buttonList.size(); ++i)
				m_buttonList[i]->SetActive(true);
		}
		else 
		{
			//Renders full page
			for (unsigned i = *m_current_page * m_num_item_per_page; i < *m_current_page * m_num_item_per_page + m_num_item_per_page; ++i)
				m_buttonList[i]->SetActive(true);
		}
	}
}

//Renders the menu
void Shop_Menu::Render()
{
	//If all items can be fit in one page
	if (m_buttonList.size() / m_num_item_per_page == 0)
	{
		for (unsigned i = 0; i < m_buttonList.size(); ++i)
				m_buttonList[i]->Render();
	}
	else
	{	
		//Start rendering "start" of page
		if (*m_current_page * m_num_item_per_page >= m_buttonList.size() / m_num_item_per_page)
		{
			for (unsigned i = *m_current_page * m_num_item_per_page; i < m_buttonList.size(); ++i)
					m_buttonList[i]->Render();
		}
		else
		{
			for (unsigned i = *m_current_page * m_num_item_per_page; i < *m_current_page * m_num_item_per_page + m_num_item_per_page; ++i)
					m_buttonList[i]->Render();
		}
	}
}