#include "Menu.h"
#include "MouseController.h"

Menu::Menu()
{
	m_mouse_x = 0.0;
	m_mouse_y = 0.0;
	m_position = Vector3(500,500,0);
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

		m_buttonList[i]->m_isPressed = false;

		if (checkForHover(m_buttonList[i]))
		{
			m_buttonList[i]->m_isHovered = true;

			if (MouseController::GetInstance()->IsButtonReleased(MouseController::LMB))
			{
				m_buttonList[i]->m_isPressed = true;
				m_buttonList[i]->RunFunction();
			}

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

void Shop_Menu::UpdateButtonPositions()
{
	int offset = 0;
	for (unsigned i = 0; i < m_shop_inventory->m_inventoryList.size(); ++i)
	{
		if (offset % m_num_items_per_page == 0)
			offset = 0;

		ShopItem_Button* btn = new ShopItem_Button();
		btn->SetPosition(m_position.x, (m_position.y - offset * 170) - 80);
		btn->SetActive(true);
		btn->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
		btn->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
		btn->SetTargetInventory(*m_cart_inventory);
		btn->SetItem(*m_shop_inventory->m_inventoryList[i]);
		this->AddButton(btn);

		offset++;
	}
}

void Shop_Menu::Update()
{
	Menu::Update();

	if (m_next_btn->GetIsActive())
	{
		m_next_btn->m_isPressed = false;

		if (checkForHover(m_next_btn))
		{
			m_next_btn->m_isHovered = true;

			if (MouseController::GetInstance()->IsButtonReleased(MouseController::LMB))
			{
				m_next_btn->m_isPressed = true;
				m_next_btn->RunFunction();
			}
		}
		else
			m_next_btn->m_isHovered = false;
	}

	if (m_prev_btn->GetIsActive())
	{
		m_prev_btn->m_isPressed = false;

		if (checkForHover(m_prev_btn))
		{
			m_prev_btn->m_isHovered = true;

			if (MouseController::GetInstance()->IsButtonReleased(MouseController::LMB))
			{
				m_prev_btn->m_isPressed = true;
				m_prev_btn->RunFunction();
			}
		}
		else
			m_prev_btn->m_isHovered = false;
	}

	//Loops back to start or end when out of bounds
	//Check if it's perfect pages
	if (m_buttonList.size() % m_num_items_per_page)
	{
		//when back from 0
		if (*m_current_page < 0)
			*m_current_page = (m_buttonList.size() / m_num_items_per_page);

		//when past max tab
		if (*m_current_page > m_buttonList.size() / m_num_items_per_page)
			*m_current_page = 0;
	}
	else
	{
		//when back from 0
		if (*m_current_page < 0)
			*m_current_page = (m_buttonList.size() / m_num_items_per_page) - 1;
		//when past max tab
		else if (*m_current_page >= m_buttonList.size() / m_num_items_per_page)
			*m_current_page = 0;
	}

	//Set all buttons to inactive first
	for (unsigned i = 0; i < m_buttonList.size(); ++i)
		m_buttonList[i]->SetActive(false);

	//If all items can be fit in one page
	if (m_buttonList.size() / m_num_items_per_page == 0)
	{
		for (unsigned i = 0; i < m_buttonList.size(); ++i)
			m_buttonList[i]->SetActive(true);
	}
	else
	{
		//If current page has more items than what the list is holding
		if ((*m_current_page + 1) * m_num_items_per_page > m_buttonList.size())
		{
			//Renders "leftovers"
			for (unsigned i = *m_current_page * m_num_items_per_page; i < m_buttonList.size(); ++i)
				m_buttonList[i]->SetActive(true);
		}
		else 
		{
			//Renders full page
			for (unsigned i = *m_current_page * m_num_items_per_page; i < *m_current_page * m_num_items_per_page + m_num_items_per_page; ++i)
				m_buttonList[i]->SetActive(true);
		}
	}
}

void Shop_Menu::Render()
{
	//If all items can be fit in one page
	if (m_buttonList.size() / m_num_items_per_page == 0)
	{
		for (unsigned i = 0; i < m_buttonList.size(); ++i)
				m_buttonList[i]->Render();
	}
	else
	{	
		//Start rendering "start" of page
		if (*m_current_page * m_num_items_per_page >= m_buttonList.size() / m_num_items_per_page)
		{
			for (unsigned i = *m_current_page * m_num_items_per_page; i < m_buttonList.size(); ++i)
					m_buttonList[i]->Render();
		}
		else
		{
			for (unsigned i = *m_current_page * m_num_items_per_page; i < *m_current_page * m_num_items_per_page + m_num_items_per_page; ++i)
					m_buttonList[i]->Render();
		}
	}

	m_next_btn->Render();
	m_prev_btn->Render();
}

void Cart_Menu::InitialiseButtons()
{
	ClearButtonList();
	float offset_x = m_position.x;
	float offset_y = m_position.y;

	//Add a button for each inventory item
	for (unsigned i = 0; i < m_targetInventory->m_inventoryList.size(); ++i)
	{
		if (i % m_num_item_per_row == 0)
		{
			offset_x = 0;
			offset_y -= 100;
		}
		else
			offset_x += 100;

		ShopCart_Button* button = new ShopCart_Button();
		button->SetIndex(i);
		button->SetActive(true);
		button->SetTargetInventory(*m_targetInventory);
		button->SetPosition(m_position.x + offset_x, offset_y);
		button->SetScale(100, 100);
		button->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
		button->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
		m_buttonList.push_back(button);
	}
}

void SellingCart_Menu::InitialiseButtons()
{
	ClearButtonList();
	float offset_x = m_position.x;
	float offset_y = m_position.y;

	//Add a button for each inventory item
	for (unsigned i = 0; i < m_targetInventory->m_inventoryList.size(); ++i)
	{
		if (i % m_num_item_per_row == 0)
		{
			offset_x = 0;
			offset_y -= 100;
		}
		else
			offset_x += 100;

		TransferToInventory_Button* button = new TransferToInventory_Button();
		button->SetIndex(i);
		button->SetActive(true);
		button->SetTargetInventory(*m_targetInventory);
		button->SetReceivingInventory(*m_receiving_inventory);
		button->SetPosition(m_position.x + offset_x, offset_y);
		button->SetScale(100, 100);
		button->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
		button->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
		m_buttonList.push_back(button);
	}
}