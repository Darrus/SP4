#pragma once

#include "Scene.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "../FPSCamera.h"
#include "../Entity/SpriteEntity.h"
#include "../Entity/Entity2D.h"

#include "../Menu/Menu.h"

#include "../Items/Inventory.h"
#include "../Items/Item.h"
#include "../Items/Consumable.h"
#include "../Items/Equipment.h"
#include "../Entity/ParticleEntity.h"

class SceneManager;
class TextEntity;

class ShopScene : public Scene
{
public:
	ShopScene();
	~ShopScene();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	Menu* menu;

private:
	FPSCamera camera;
	SpriteEntity* IntroStateBackground;
	Entity2D entity;

	Inventory* inventory;
	Inventory* cart;

	ParticleEntity* particle;
};


//Button Functions
void ButtonFunc();