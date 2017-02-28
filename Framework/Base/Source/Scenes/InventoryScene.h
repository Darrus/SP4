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

class InventoryScene : public Scene
{
public:
	InventoryScene();
	~InventoryScene();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Pause();

private:
	FPSCamera camera;

	//Inventory
	Inventory* player_inventory;

	//Reuse the Shop Menu for display 
	Inventory_Menu* display_inventory;
	int current_page;

	CharacterInfo* dummy_party[4];
	SelectCharacterForItem_Button* chara_select_btn[4];
	Menu* character_menu;

	//for using items
	Item* item_holder;
	CharacterInfo* chara_holder;
	int item_index;

	PopUp_Button* used_item;

	Menu* utilitybuttons;

	void init_inventory();
};