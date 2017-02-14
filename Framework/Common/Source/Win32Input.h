/******************************************************************************/
/*!
\file	Win32Input.h
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

#ifndef WIN32_INPUT_H
#define WIN32_INPUT_H

#include <stack>
#include <bitset>
#include <windows.h>
#include <queue>

/******************************************************************************/
/*!
		enum InputMap:
\brief	enumerations of keyboard keys ID
*/
/******************************************************************************/
namespace InputMap {
	enum ID {
		INVALID,
		BACKSPACE,
		TAB,
		RETURN,
		SHIFT,
		CONTROL,
		ESCAPE,
		SPACE,
		ARROW_UP,
		ARROW_DOWN,
		ARROW_LEFT,
		ARROW_RIGHT,
		N_0,
		N_1,
		N_2,
		N_3,
		N_4,
		N_5,
		N_6,
		N_7,
		N_8,
		N_9,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		MOUSE_LEFT,
		MOUSE_RIGHT,
		MOUSE_MIDDLE,
		MOUSE_WHEEL,
		PLUS,
		MINUS,
		LAST,
	}; //end enum ID
} //end namespace InputMap

/******************************************************************************/
/*!
\brief	InputMap functions
*/
/******************************************************************************/
InputMap::ID GetKey(WPARAM wp);

/******************************************************************************/
/*!
		Class Input:
\brief	Input class and related methods
*/
/******************************************************************************/
class Input {
public:
	void Reset(void);

	//To Check key status
	bool IsPressed(InputMap::ID key) const;
	bool IsTriggered(InputMap::ID key) const;
	bool IsRepeating(InputMap::ID key) const;

	bool IsAnyPressed(void) const;
	bool IsAnyTriggered(void) const;

	void SetPressed(InputMap::ID key, bool status);

	//Mouse controls
	int GetMouseX(void) const;
	int GetMouseY(void) const;
	
	int GetMouseDX(void) const;
	int GetMouseDY(void) const;

	void SetMouseX(int x);
	void SetMouseY(int y);

	void SetWheelDelta(int delta);
	int GetWheelDelta(void) const;

	typedef std::queue<InputMap::ID> KeySequence;
	KeySequence keySequence;

	InputMap::ID LastTriggered(void);
	int LastClicked(void);
	void SetLastClicked(int click);

private:
	typedef std::stack<InputMap::ID> IDStack;

	IDStack m_unpress;
	std::bitset<InputMap::LAST> m_pressed;
	std::bitset<InputMap::LAST> m_triggered;
	std::bitset<InputMap::LAST> m_repeating;

	int mouseX;
	int mouseY;
	int mouseDX;
	int mouseDY;
	int wheelDelta;

	InputMap::ID lastTriggered;
	int lastClicked;
	
}; //end class Input

#endif
