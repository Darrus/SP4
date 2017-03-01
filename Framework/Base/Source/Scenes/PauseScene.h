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
	Menu* pause_menu;

public:
	PauseScene();
	virtual ~PauseScene();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

