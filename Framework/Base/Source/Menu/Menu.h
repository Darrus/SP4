#ifndef MENU_H
#define MENU_H

#include "../Application.h"
#include "Button.h"
#include <vector>

using std::vector;

class Menu
{
private:

	double m_mouse_x;
	double m_mouse_y;

public:

	//HACK
	vector <Button*> m_buttonList;

	//Adds a new button to the list
	inline void AddButton(Button* addButton) { m_buttonList.push_back(addButton); }

	//Checks if buttons are pressed
	void Update();

	//Renders the menu
	void Render();

	Menu();
	~Menu();
};


#endif