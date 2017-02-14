/******************************************************************************/
/*!
\file	Win32Input.cpp
\author Wen Sheng Tang
\par	email: wensheng.tang\@digipen.edu
\par	wensheng.tang
\par	Course: CS1050
\par	Project #02
\date	25/11/2010
\brief
Define the Input class that captures key/mouse inputs
Copyright (C) 2010 DigiPen Institute of Technology
*/
/******************************************************************************/

#include "Win32Input.h"
	
/******************************************************************************/
/*!
\brief
Reset/clear all buffered inputs
*/
/******************************************************************************/
void Input::Reset(void) {
	mouseDX = mouseDY = 0;
	m_triggered.reset();
	m_repeating.reset();
	while(!m_unpress.empty()) {
		m_pressed[m_unpress.top()] = false;
		m_unpress.pop();
	}
}

/******************************************************************************/
/*!
\brief
Check if a certain key is pressed

\param key
	key to check for
\return 
	True if key is pressed
*/
/******************************************************************************/
bool Input::IsPressed(InputMap::ID key) const {
	if(key > InputMap::INVALID && key < InputMap::LAST)
		return m_pressed[key];
	return false;
}

/******************************************************************************/
/*!
\brief
Check if a certain key is triggered

\param key
	key to check for
\return 
	True if key is triggered
*/
/******************************************************************************/
bool Input::IsTriggered(InputMap::ID key) const {
	if(key > InputMap::INVALID && key < InputMap::LAST)
		return m_triggered[key];
	return false;
}

/******************************************************************************/
/*!
\brief
Check if a certain key is repeatedly pressed

\param key
	key to check for
\return 
	True if key is repeatedly pressed
*/
/******************************************************************************/
bool Input::IsRepeating(InputMap::ID key) const {
	if(key > InputMap::INVALID && key < InputMap::LAST)
		return m_repeating[key];
	return false;
}

/******************************************************************************/
/*!
\brief
Check if any key is pressed

\return 
	True if any key is pressed
*/
/******************************************************************************/
bool Input::IsAnyPressed(void) const {
	return m_pressed.any();
}

/******************************************************************************/
/*!
\brief
Check if any key is triggered

\return 
	True if any key is triggered
*/
/******************************************************************************/
bool Input::IsAnyTriggered(void) const {
	return m_triggered.any();
}

/******************************************************************************/
/*!
\brief
Set a key status

\param key
	key to set
\param status
	true if pressed, false if unpressed
*/
/******************************************************************************/
void Input::SetPressed(InputMap::ID key, bool status) {
	if(key > InputMap::INVALID && key < InputMap::LAST) {
		if(status) {
			if(m_pressed[key] == false) {
				m_pressed[key] = true;
				m_triggered[key] = true;
				lastTriggered = key;
			}
			else {
				m_repeating[key] = true;
			}
		}
		else {
			m_unpress.push(key);
		}
	}
}

/******************************************************************************/
/*!
\brief
Get Mouse click x-coordinate

\return 
	Mouse click x-coordinate
*/
/******************************************************************************/
int Input::GetMouseX(void) const {
	return mouseX;
}

/******************************************************************************/
/*!
\brief
Get Mouse click y-coordinate

\return 
	Mouse click y-coordinate
*/
/******************************************************************************/
int Input::GetMouseY(void) const {
	return mouseY;
}

/******************************************************************************/
/*!
\brief
Get change in Mouse click x-coordinate

\return 
	Change in Mouse click x-coordinate
*/
/******************************************************************************/
int Input::GetMouseDX(void) const {
	return mouseDX;
}

/******************************************************************************/
/*!
\brief
Get change in Mouse click y-coordinate

\return 
	Change in Mouse click y-coordinate
*/
/******************************************************************************/
int Input::GetMouseDY(void) const {
	return mouseDY;
}

/******************************************************************************/
/*!
\brief
Set Mouse click x-coordinate

\param x
	x-coordinate of Mouse click
*/
/******************************************************************************/
void Input::SetMouseX(int x) {
	mouseDX = x - mouseX;
	mouseX = x;
}

/******************************************************************************/
/*!
\brief
Set Mouse click y-coordinate

\param y
	y-coordinate of Mouse click
*/
/******************************************************************************/
void Input::SetMouseY(int y) {
	mouseDY = y - mouseY;
	mouseY = y;
}

/******************************************************************************/
/*!
\brief
Get the last triggered key

\return
	Key ID
*/
/******************************************************************************/
InputMap::ID Input::LastTriggered(void) {
	return lastTriggered;
}

/******************************************************************************/
/*!
\brief
Get the last clicked button (LEFT, RIGHT, MIDDLE)

\return
	Key ID
*/
/******************************************************************************/
int Input::LastClicked(void) {
	return lastClicked;
}

/******************************************************************************/
/*!
\brief
Set the last clicked button (LEFT, RIGHT, MIDDLE)

\param
	KEY ID
*/
/******************************************************************************/
void Input::SetLastClicked(int click) {
	lastClicked = click;
}

void Input::SetWheelDelta(int delta) {
	wheelDelta = delta;
}

int Input::GetWheelDelta(void) const {
	return wheelDelta;
}

/******************************************************************************/
/*!
\brief
Return the key/mouse that is pressed

\param wp
	windows parameter that contains key/mouse input
*/
/******************************************************************************/
InputMap::ID GetKey(WPARAM wp) {
	switch(wp) {
	case VK_RETURN:  return InputMap::RETURN;
	case VK_SPACE:   return InputMap::SPACE;
	case VK_UP:      return InputMap::ARROW_UP;
	case VK_DOWN:    return InputMap::ARROW_DOWN;
	case VK_LEFT:    return InputMap::ARROW_LEFT;
	case VK_RIGHT:   return InputMap::ARROW_RIGHT;
	case VK_TAB:     return InputMap::TAB;
	case VK_SHIFT:   return InputMap::SHIFT;
	case VK_CONTROL: return InputMap::CONTROL;
	case VK_ESCAPE:  return InputMap::ESCAPE;
	case VK_BACK:    return InputMap::BACKSPACE;
	case VK_OEM_PLUS:	 return InputMap::PLUS;
	case VK_OEM_MINUS:	 return InputMap::MINUS;
	default:
		if(wp >= 'A' && wp <= 'Z')
			return (InputMap::ID)(InputMap::A + (wp - 'A'));
		if(wp >= '0' && wp <= '9')
			return (InputMap::ID)(InputMap::N_0 + (wp - '0'));
		return InputMap::INVALID;
	}
}
