#ifndef MENU_H
#define MENU_H

#include "../Application.h"
#include "Button.h"
#include <vector>

using std::vector;

class Menu
{
protected:
	double m_mouse_x;
	double m_mouse_y;

	bool checkForHover(Button* btn);

public:
	vector <Button*> m_buttonList;
	Vector3 m_position;

	inline void SetPosition(float pos_x, float pos_y) { m_position.x = pos_x; m_position.y = pos_y; }

	//Adds a new button to the list
	inline void AddButton(Button* addButton) { m_buttonList.push_back(addButton); }

	//Sets if menu is interactable
	inline void SetActive(bool isActive) 
	{
		if (isActive)
			for (unsigned i = 0; i < m_buttonList.size(); ++i)
				m_buttonList[i]->SetActive(true);
		else
			for (unsigned i = 0; i < m_buttonList.size(); ++i)
				m_buttonList[i]->SetActive(false);
	}

	inline virtual void ClearButtonList()
	{
		//delete the current buttonlist
		for (auto it = m_buttonList.begin(); it != m_buttonList.end(); ++it)
			delete *it;

		m_buttonList.clear();
	}

	//Checks if buttons are pressed
	virtual void Update();

	//Renders the menu
	virtual void Render();

	Menu();
	virtual ~Menu();
};



//======================================================================================//



class Shop_Menu : public Menu
{
protected:
	int *m_current_page;
	int m_num_items_per_page;
	Inventory *m_shop_inventory;
	Inventory *m_cart_inventory;
	Increment_Button* m_prev_btn;
	Increment_Button* m_next_btn;

public:
	//Getters and Setters
	inline void SetStoreInventory(Inventory* shop_inventory){ m_shop_inventory = shop_inventory; }
	inline void SetCartInventory(Inventory* cart_inventory){ m_cart_inventory = cart_inventory; }
	inline void SetCurrentPage(int &currentPage) { m_current_page = &currentPage; }
	inline void SetItemsPerPage(int item_per_page){ m_num_items_per_page = item_per_page; }
	inline void SetPreviousButton(Increment_Button* prev_btn){ m_prev_btn = prev_btn; }
	inline void SetNextButton(Increment_Button* next_btn){ m_next_btn = next_btn; }

	inline int GetCurrentPage() { return *m_current_page; }
	inline int GetNumberOfItemsPerPage() { return m_num_items_per_page; }

	virtual void UpdateButtonPositions();

	//Checks if buttons are pressed
	virtual void Update();

	//Renders the menu
	virtual void Render();
	virtual void Close(){};

	Shop_Menu() : m_current_page(0){};
	virtual ~Shop_Menu(){};
};


//======================================================================================//


class Cart_Menu : public Menu
{
protected:
	int m_num_item_per_row;
	int m_max_num_coloumns;

	Inventory *m_targetInventory;

public:
	//Getters and Setters
	inline int GetMaxNumberOfColumns(){ return m_max_num_coloumns; }

	//Cart's Inventory
	inline void SetTargetInventory(Inventory &target_inven){ m_targetInventory = &target_inven; }
	inline void SetNumberItemsPerRow(int num_rows){ m_num_item_per_row = num_rows; }
	inline void SetMaxNumberOfColumns(int num_columns){ m_max_num_coloumns = num_columns; }

	void InitialiseButtons();

	inline void Update()
	{
		Menu::Update();
		InitialiseButtons();
	}

	virtual inline void Render()
	{
		Menu::Render();
	}

	Cart_Menu() : m_num_item_per_row(5){};
	~Cart_Menu(){};
};



//======================================================================================//



class SellingCart_Menu : public Cart_Menu
{
protected:
	Inventory *m_receiving_inventory;

public:
	inline void Update()
	{
		Menu::Update();
		InitialiseButtons();
	}

	inline void SetReceivingInventory(Inventory &recv_inven){ m_receiving_inventory = &recv_inven; }
	void InitialiseButtons();

	SellingCart_Menu() : Cart_Menu(){};
	~SellingCart_Menu(){};
};

#endif