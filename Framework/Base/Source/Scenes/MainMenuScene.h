#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "Scene.h"
#include "../FPSCamera.h"
#include "../Menu/Button.h"
#include "../Menu/Menu.h"

class SceneManager;
class TextEntity;

class MainMenuScene : public Scene

{
public:
	GUIObject* background;

	MainMenuScene();
	~MainMenuScene();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

private:
	FPSCamera camera;

	//Menus
	Menu* utility_menu;	
};

#endif