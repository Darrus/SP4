#pragma once
#include <vector>
#include <string>

#include "Scene.h"
#include "../Menu/Menu.h"
#include "../Menu/CharacterProfile_Button.h"

using std::vector;
using std::string;

class PartyScene : public Scene
{
protected:
	//Remove buttons
	RemoveMember_Button* remove_btn[4];
	
	//Buttons to press to view character profile
	CharacterProfile_Button* chara_btn[4];

	//Popup button
	PopUp_Button* prompt;

	Menu* utility_menu;

public:
	PartyScene();
	virtual ~PartyScene();

	void InitialiseCharacterButtons();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void UnPause();
};

