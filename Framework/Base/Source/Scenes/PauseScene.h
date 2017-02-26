#pragma once
#include <vector>
#include <string>

#include "Scene.h"
#include "../Menu/Menu.h"
#include "../Menu/Button.h"

using std::vector;
using std::string;

class PauseScene : public Scene
{
protected:
	PreviousScene_Button* unpause_btn;
	ChangeScene_Button* inventory_btn;
	ChangeScene_Button* party_btn;
	ChangeScene_Button* options_btn;

	Menu* pause_menu;

public:
	PauseScene();
	virtual ~PauseScene();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

