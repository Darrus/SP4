#ifndef BUTTON_H
#define BUTTON_H

#include "Mesh.h"
#include "GUIObject.h"
#include "../Items/Inventory.h"
#include "../../Common/Source/SceneManager.h"

#include <iostream>
#include <string>

using std::string;

enum BUTTON_MESH
{
	NORMAL_IMAGE = false,
	HIGHLIGHTED_IMAGE,

	NUM_IMAGES
};

//===============================================================//
//Brief: A button object that does something on Press			 //
//===============================================================//
class Button : public GUIObject
{
protected:
	//Holds the image and highlighted image
	Mesh* m_meshList[NUM_IMAGES];

	//boolean to set if the button is clickable
	bool m_isClickable;

public:
	//To determine which mesh is rendered
	bool m_isHovered;
	
	inline bool GetIsClickable(){ return m_isClickable; }

	inline void SetClickable(bool clickable) { m_isClickable = clickable; }
	inline void SetImage(Mesh* image) { m_meshList[NORMAL_IMAGE] = image; }
	inline void SetHighlightedImage(Mesh* image) { m_meshList[HIGHLIGHTED_IMAGE] = image; }

	//Virtual function that runs specified button functionality
	inline virtual void RunFunction() = 0;

	//Renders the button
	virtual void Render();

	Button();
	Button(float pos_x, float pos_y, float scale_x, float scale_y);

	inline virtual ~Button(){};
};

//===============================================================//
//Brief: A button object that toggles a boolean		             //
//===============================================================//
class Toggle_Button : public Button
{
protected:
	//Pointer that points to the address of the boolean to toggle
	bool *m_toToggle;

public:
	//Setters
	inline void SetSwitch(bool &to_toggle){ m_toToggle = &to_toggle; }

	//Virtual function from button class that runs specified button functionality
	inline void RunFunction(){ *m_toToggle = !*m_toToggle; }
	virtual void Render();

	Toggle_Button() : m_toToggle(nullptr){};
	~Toggle_Button(){};
};

//===============================================================//
//Brief: A button object that sets a boolean to a specific value //
//===============================================================//
class SetBool_Button : public Toggle_Button
{
protected:
	//Boolean to set to
	bool m_desired_bool;

public:
	//Always set the boolean to true
	inline void SetBoolean(bool setbool){ m_desired_bool = setbool; }
	inline void RunFunction(){ *m_toToggle = m_desired_bool; }
	void Render();

	SetBool_Button() : Toggle_Button(){};
	~SetBool_Button(){};
};

//===============================================================//
//Brief: A button object that increases an integer				 //
//===============================================================//
class Increment_Button : public Button
{
protected:
	//Pointer that points to the address of the value to increment
	int *m_toIncrease;
	//Amount to increament 
	int m_increment;

public:
	//Setters
	inline void SetTargetValue(int &to_increase){ m_toIncrease = &to_increase; }
	inline void SetIncrementAmount(int value){ m_increment = value; }

	//Virtual function from button class that runs specified button functionality
	inline void RunFunction(){ *m_toIncrease += m_increment; }

	Increment_Button() : m_toIncrease(nullptr), m_increment(1){};
	~Increment_Button(){};
};

//============================================================================//
//Brief: A button object that adds a copy of a set item into target inventory.//
//============================================================================//

class ChangeScene_Button : public Button
{
protected:
	string m_desired_scene;

public:
	//Getters and Setters
	inline void SetDesiredScene(string value){ m_desired_scene = value; }

	inline void RunFunction(){ SceneManager::GetInstance()->SetActiveScene(m_desired_scene); }

	ChangeScene_Button(){}
	~ChangeScene_Button(){}
};

//===============================================================================//
//Brief: A button object that changes the value of the target to a desired value.//
//===============================================================================//

class ChangeValue_Button : public Button
{
protected:
	//Pointer that points to the address of the value to increment
	int *m_set_value;
	//Amount to increament 
	int m_target_value;

public:
	//Getters and Setters
	inline void SetTargetValue(int &set_value){ m_set_value = &set_value; }

	inline void RunFunction(){ *m_set_value = m_target_value; }

	ChangeValue_Button(){}
	~ChangeValue_Button(){}
};

//============================================================================//
//Brief: A button object that adds a copy of a set item into target inventory.//
//============================================================================//
class ShopItem_Button : public Button
{
protected:
	Item *m_item;
	Inventory *m_targetInventory;

public:
	inline void SetTargetInventory(Inventory &target_inven){ m_targetInventory = &target_inven; }
	inline void SetItem(Item &target_item){ m_item = &target_item; }
	inline void RunFunction()
	{ 
		Item* itemToAdd = new Item();
		*itemToAdd = *m_item;
		m_targetInventory->AddItem(itemToAdd);
	}
	virtual void Render();

	ShopItem_Button()
	{
		//Scale ratio of about 3:1 is ideal
		SetScale(650, 150);
	};
	~ShopItem_Button(){};
};

//============================================================================//
//Brief: A button object that hold the index of an Item object and			  //
//		 then disappears when pressed.										  //
//============================================================================//
class ShopCart_Button : public Button
{
protected:
	int m_item_index;
	Inventory *m_targetInventory;

public: 
	inline void SetIndex(int item_index){ m_item_index = item_index; }
	inline void SetTargetInventory(Inventory &target_inven){ m_targetInventory = &target_inven; }

	inline void RunFunction()
	{
		m_targetInventory->m_inventoryList.erase(m_targetInventory->m_inventoryList.begin() + m_item_index);
		
		m_isActive = false;
	}

	void Render();

	ShopCart_Button() : Button(){};
	~ShopCart_Button(){};
};


#endif