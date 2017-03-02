#ifndef LOAD_GAME_SCENE_H
#define LOAD_GAME_SCENE_H

#include "Scene.h"
#include "../FPSCamera.h"
#include "../Menu/Button.h"
#include "../Menu/Menu.h"

class SceneManager;
class TextEntity;

class LoadGameScene : public Scene
{
public:
	LoadGameScene();
	~LoadGameScene();
	GUIObject* background;

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