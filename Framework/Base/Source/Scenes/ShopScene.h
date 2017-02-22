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


private:
	FPSCamera camera;
	Entity2D entity;

	//Inventory
	Inventory* shop_inventory;
	Inventory* cart_inventory;
	Inventory* player_inventory;

	//Utility buttons
	bool acceptpurchase;
	void SendToPlayerInventory();
	int currentPage = 0;
	
	//Menus
	Shop_Menu* shop_menu;
	Menu* utilitybuttons;
	Cart_Menu* cart_menu;
};