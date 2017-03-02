#pragma once
#include <vector>
#include <string>

#include "Scene.h"
#include "../Menu/Menu.h"
#include "../Menu/CharacterProfile_Button.h"

using std::vector;
using std::string;

class TavernScene : public Scene
{
protected:
	//Function that creates random characters to hire
	CharacterInfo* generate_random_character();

	//Dummy holder for party to be taken from player class
	CharacterInfo* tavern_slots[4];
	
	//Buttons to press to view character profile
	CharacterProfile_Button* chara_btn[4];
	Hire_Button* hire_btn[4];

	//Pop-up button to send player notifications
	PopUp_Button* prompt;

	//GUIObjects
	GUIObject* gold_display;
	GUIObject* tavern_display;
	GUIObject* background;

	//Menu to holdsome utility buttons
	Menu* utility_menu;

public:
	TavernScene();
	virtual ~TavernScene();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Pause();
	virtual void UnPause();
};

