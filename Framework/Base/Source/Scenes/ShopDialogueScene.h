#pragma once
#include <vector>
#include <string>

#include "Scene.h"
#include "../Entity/TextEntity.h"
#include "../Entity/SpriteEntity.h"
#include "../Menu/Menu.h"
#include "../Menu/Button.h"

using std::vector;
using std::string;

class ShopDialogueScene : public Scene
{
	vector<string> dialogue;
	string targetScene;
	TextEntity* text;
	SpriteEntity* textBG;
	GUIObject* characterPortrait;

	//Dialogue stuff
	Toggle_Button* inMenu;
	Menu* dialogue_menu;

	int textPos;
	bool dialogue_options;

public:
	ShopDialogueScene();
	virtual ~ShopDialogueScene();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

	virtual void Pause();

	inline void SetDialogue(vector<string> dialogue)
	{ 
		this->dialogue = dialogue; 
		textPos = 0;
	}
	void SetTargetScene(string targetScene){ this->targetScene = targetScene; }
};

