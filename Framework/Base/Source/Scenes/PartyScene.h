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
	PreviousScene_Button* back_btn;

	//Dummy holder for party to be taken from player class
	CharacterInfo* chara_info[4];
	
	//Buttons to press to view character profile
	CharacterProfile_Button* chara_btn[4];

	Menu* utility_menu;

public:
	PartyScene();
	virtual ~PartyScene();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

