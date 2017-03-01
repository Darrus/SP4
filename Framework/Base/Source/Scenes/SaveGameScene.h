#ifndef SAVE_GAME_SCENE_H
#define SAVE_GAME_SCENE_H

#include "Scene.h"
#include "../FPSCamera.h"
#include "../Menu/Button.h"
#include "../Menu/Menu.h"

class SceneManager;
class TextEntity;

class SaveGameScene : public Scene
{
public:
	SaveGameScene();
	~SaveGameScene();

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