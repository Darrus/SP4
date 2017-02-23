#ifndef GUI_OBJECT_H
#define GUI_OBJECT_H

#include "../Application.h"
#include "RenderHelper.h"
#include "GraphicsManager.h"
#include "MeshBuilder.h"

#include <string>

using std::string;

class GUIObject
{
protected:
	//Generic Mesh* for if the GUI Object has an image
	Mesh* m_image;

	//Holds the text to render with the GUI Object
	string m_text;
	float m_text_offset_x, m_text_offset_y;
	float m_text_scale_x, m_text_scale_y;

	//Position and scale of GUI Object in world space
	float m_pos_x, m_pos_y;
	float m_scale_x, m_scale_y;

	//Position and scale of GUI Object in screen space
	float m_screen_pos_x, m_screen_pos_y;
	float m_screen_scale_x, m_screen_scale_y;

	//boolean to set if the GUI Object is active
	bool m_isActive;

public:
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

	inline void SetPosition(float x, float y, bool update_screen_space = true)
	{
		m_pos_x = x;
		m_pos_y = y;

		if (update_screen_space)
		{
			m_screen_pos_x = m_pos_x / Application::GetInstance().GetWindowWidth();
			m_screen_pos_y = m_pos_y / Application::GetInstance().GetWindowHeight();
		}
	}
	inline void SetScale(float x, float y, bool update_screen_space = true)
	{
		m_scale_x = x;
		m_scale_y = y;

		if (update_screen_space)
		{
			m_screen_scale_x = m_scale_x / Application::GetInstance().GetWindowWidth();
			m_screen_scale_y = m_scale_y / Application::GetInstance().GetWindowHeight();
		}
	}
	inline void SetImage(Mesh* image) { m_image = image; }
	inline void SetTextOffset(float text_x, float text_y){ m_text_offset_x = text_x; m_text_offset_y = text_y; };
	inline void SetTextScale(float text_x, float text_y){ m_text_scale_x = text_x; m_text_scale_y = text_y; };
	inline void SetText(string text) { m_text = text; }
	inline void SetActive(bool active){ m_isActive = active; }

	//Each derived class should have their own Render
	virtual void Render()
	{
		if (!m_isActive)
			return;
		MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
		modelStack.PushMatrix();
		modelStack.Translate(m_pos_x, m_pos_y, 0);

		modelStack.PushMatrix();
		modelStack.Scale(m_scale_x, m_scale_y, 1);
		RenderHelper::RenderMesh(m_image);
		modelStack.PopMatrix();

		if (m_text != "")
		{
			//Offset for text
			modelStack.Translate(-m_scale_x * 0.5, 0, 1);
			modelStack.Translate(m_text_offset_x, m_text_offset_y, 0);
			modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
			RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), m_text, Color(1, 0, 0));	//NOTE: COLOUR DOESN'T WORK. THANKS ALOT, TOH.
		}

		modelStack.PopMatrix();
	};

	GUIObject() :
		m_pos_x(500.0f),
		m_pos_y(500.0f),
		m_scale_x(100.f),
		m_scale_y(100.f), 
		m_text(""),
		m_text_offset_x(0),
		m_text_offset_y(0),
		m_text_scale_x(30),
		m_text_scale_y(30.f),
		m_isActive(true){}
	virtual ~GUIObject(){}
};


#endif