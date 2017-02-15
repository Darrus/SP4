#ifndef BUTTON_H
#define BUTTON_H

#include "Mesh.h"
#include <string>

using std::string;

enum BUTTON_MESH
{
	NORMAL_IMAGE = 0,
	HIGHLIGHTED_IMAGE,

	NUM_IMAGES
};

typedef void(*FunctionPointer) (void);

class Button
{
private:
	//To determine which mesh is rendered
	bool m_isHovered;

	//Position and scale of button
	float m_pos_x, m_pos_y;
	float m_scale_x, m_scale_y;

	//Holds the fuction to run when button is pressed
	FunctionPointer m_function;

	//Holds the image and highlighted image
	Mesh* m_meshList[NUM_IMAGES];

	//Holds the text to render with the image
	string m_text;
	//TODO:
	//Add stuff to fine tune the text
	//text_offset, text_scale, .etc

public:
	//Getters and Setters
	inline float GetPositionX() { return m_pos_x; }
	inline float GetPositionY() { return m_pos_y; }
	inline float GetScaleX() { return m_scale_x; }
	inline float GetScaleY() { return m_scale_y; }

	inline void SetPosition(float x, float y) { m_pos_x = x; m_pos_y = y; }
	inline void SetScale(float x, float y) { m_scale_x = x; m_scale_y = y; }
	inline void SetImage(Mesh* image) { m_meshList[NORMAL_IMAGE] = image; }
	inline void SetHighlightedImage(Mesh* image) { m_meshList[HIGHLIGHTED_IMAGE] = image; }

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