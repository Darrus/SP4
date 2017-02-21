#pragma once

#include "Scene.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "../FPSCamera.h"

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
	Shop_Menu* itemtabs;
	Menu* utilitybuttons;

private:
	FPSCamera camera;
	Entity2D entity;

	Inventory* shop_inventory;
	Inventory* cart_inventory;
	Inventory* player_inventory;

	bool acceptpurchase;
	void SendToPlayerInventory();

	bool buyingTab;
	int currentPage = 0;

	Cart_Menu* cart_menu;

	ParticleEntity* particle;
};