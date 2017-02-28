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
	virtual void Pause();
	virtual void UnPause();

private:
	FPSCamera camera;

	//Inventory
	Inventory* shop_inventory;
	Inventory* cart_inventory;
	Inventory* player_inventory;

	//Utility buttons
	bool b_accept;
	void SendToPlayerInventory();
	int currentPage = 0;

	//For Purchasing items
	SetBool_Button* acceptpurchasebtn;

	GUIObject* cart_amount;
	GUIObject* player_gold_amount;
	GUIObject* inventory_display;

	int cart_cost;
	int temp_player_gold;

	//Not enough gold pop button
	PopUp_Button* prompt;
	
	Toggle_Button* tgle_btn;
	bool buying_tab;

	//Menus
	Shop_Menu* shop_menu;	
	Cart_Menu* cart_menu;

	SellingCart_Menu* player_selling_menu;
	SellingCart_Menu* shop_selling_menu;

	Menu* utilitybuttons;
};