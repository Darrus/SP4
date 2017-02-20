#ifndef BUTTON_H
#define BUTTON_H

#include "Mesh.h"
#include "../Application.h"
#include "../Items/Inventory.h"

#include "../../Common/Source/MyMath.h"

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
class Button
{
protected:
	//Position and scale of button in world space
	float m_pos_x, m_pos_y;
	float m_scale_x, m_scale_y;
	
	//Position and scale of button in screen space
	float m_screen_pos_x, m_screen_pos_y;
	float m_screen_scale_x, m_screen_scale_y;

	//Holds the image and highlighted image
	Mesh* m_meshList[NUM_IMAGES];

	//Holds the text to render with the image
	string m_text;
	float m_text_offset_x, m_text_offset_y;
	float m_text_scale_x, m_text_scale_y;

	//boolean to set if the button is active
	bool m_isActive;

	//boolean to set if the button is clickable
	bool m_isClickable;

public:

	//To determine which mesh is rendered
	bool m_isHovered;

	//Getters and Setters
	inline float GetPositionX() { return m_pos_x; }
	inline float GetPositionY() { return m_pos_y; }
	inline float GetScaleX() { return m_scale_x; }
	inline float GetScaleY() { return m_scale_y; }

	inline float GetScreenPositionX() { return m_screen_pos_x; }
	inline float GetScreenPositionY() { return m_screen_pos_y; }
	inline float GetScreenScaleX() { return m_screen_scale_x; }
	inline float GetScreenScaleY() { return m_screen_scale_y; }

	inline bool GetIsActive(){ return m_isActive; }
	inline bool GetIsClickable(){ return m_isClickable; }

	inline void SetPosition(float x, float y) 
	{
		m_pos_x = x;
		m_pos_y = y; 
	
		m_screen_pos_x = m_pos_x / Application::GetInstance().GetWindowWidth();
		m_screen_pos_y = m_pos_y / Application::GetInstance().GetWindowHeight();
	}
	inline void SetScale(float x, float y) 
	{ 
		m_scale_x = x; 
		m_scale_y = y; 
	
		m_screen_scale_x = m_scale_x / Application::GetInstance().GetWindowWidth();
		m_screen_scale_y = m_scale_y / Application::GetInstance().GetWindowHeight();
	}
	inline void SetTextOffset(float text_x, float text_y){ m_text_offset_x = text_x; m_text_offset_y = text_y; };
	inline void SetTextScale(float text_x, float text_y){ m_text_scale_x = text_x; m_text_scale_y= text_y; };
	inline void SetImage(Mesh* image) { m_meshList[NORMAL_IMAGE] = image; }
	inline void SetHighlightedImage(Mesh* image) { m_meshList[HIGHLIGHTED_IMAGE] = image; }
	inline void SetText(string text) { m_text = text; }
	inline void SetActive(bool active){ m_isActive = active; }
	inline void SetClickable(bool clickable) { m_isClickable = clickable; }

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
	inline void SetNumber(int &to_increase){ m_toIncrease = &to_increase; }
	inline void SetIncrementAmount(int value){ m_increment = value; }

	//Virtual function from button class that runs specified button functionality
	inline void RunFunction(){ *m_toIncrease += m_increment; }

	Increment_Button() : m_toIncrease(nullptr), m_increment(19){};
	~Increment_Button(){};
};

//============================================================================//
//Brief: A button object that adds a copy of a set item into target inventory //
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

#endif