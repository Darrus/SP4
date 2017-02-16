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
	NORMAL_IMAGE = 0,
	HIGHLIGHTED_IMAGE,

	NUM_IMAGES
};

typedef void(*FunctionPointer) (void);

struct RandomPos
{
	inline void operator() (float &x, float &y, float &screen_x, float &screen_y)
	{
		x = Math::RandFloatMinMax(250, 500);
		y = Math::RandFloatMinMax(250, 500);

		screen_x = x / Application::GetInstance().GetWindowWidth();
		screen_y = y / Application::GetInstance().GetWindowHeight();
	}
};

//======================================//
//TODO:									//
//Use function pointers to Lua instead	//
//======================================//

class Button
{
private:
	//Position and scale of button in world space
	float m_pos_x, m_pos_y;
	float m_scale_x, m_scale_y;
	
	//Position and scale of button in screen space
	float m_screen_pos_x, m_screen_pos_y;
	float m_screen_scale_x, m_screen_scale_y;

	//Holds the fuction to run when button is pressed
	FunctionPointer m_function;

	//Holds the image and highlighted image
	Mesh* m_meshList[NUM_IMAGES];

	//Holds the text to render with the image
	string m_text;
	float m_text_offset_x, m_text_offset_y;
	float m_text_scale_x, m_text_scale_y;

	//TEST:
	RandomPos randompos;

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
	inline void SetImage(Mesh* image) { m_meshList[NORMAL_IMAGE] = image; }
	inline void SetHighlightedImage(Mesh* image) { m_meshList[HIGHLIGHTED_IMAGE] = image; }
	inline void SetText(string text) { m_text = text; }
	inline void SetFunction(FunctionPointer funcPtr) { m_function = funcPtr; };

	//Runs the held function
	virtual void RunFunction();

	//Renders the button
	virtual void Render();

	//Function must be initialised upon Button object creation
	Button(FunctionPointer functionToRun);
	Button(float pos_x, float pos_y, float scale_x, float scale_y, FunctionPointer &functionToRun);
	Button();

	~Button();
};

#endif