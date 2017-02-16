#ifndef BUTTON_H
#define BUTTON_H

#include "Mesh.h"
#include "../Application.h"
#include <string>

#include "../../Common/Source/MyMath.h"

#include <iostream>

using std::string;

enum BUTTON_MESH
{
	NORMAL_IMAGE = false,
	HIGHLIGHTED_IMAGE,

	NUM_IMAGES
};

//======================================//
//TODO:									//
//Use function pointers to Lua instead	//
//======================================//

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

	//Button runs what its supposed to do
	virtual void RunFunction(){};

	//Renders the button
	virtual void Render();

	Button();
	Button(float pos_x, float pos_y, float scale_x, float scale_y);

	virtual ~Button();//TODO: DELETE MESH POINTER
};

class ToggleButton : public Button
{
protected:
	bool *toToggle;

public:
	inline void SetSwitch(bool &to_toggle){ toToggle = &to_toggle; }
	inline void RunFunction(){ *toToggle = !&toToggle; }

	ToggleButton() : toToggle(nullptr){};
	~ToggleButton(){};
};

class IncrementButton : public Button
{
protected:
	int *toIncrease;

public:
	inline void SetSwitch(int &to_increase){ toIncrease = &to_increase; }
	inline void RunFunction(){ ++toIncrease; }

	IncrementButton() : toIncrease(nullptr){};
	~IncrementButton(){};
};

class DecrementButton : public Button
{
protected:
	int *toDecrease;

public:
	inline void SetSwitch(int &to_increase){ toDecrease = &to_increase; }
	inline void RunFunction(){ --toDecrease; }

	DecrementButton() : toDecrease(nullptr){}; 
	~DecrementButton(){};
};

#endif