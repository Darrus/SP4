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
	virtual void UnPause();

private:
	FPSCamera camera;

	//Inventory
	Inventory* player_inventory;

	//Reuse the Shop Menu for display 
	Inventory_Menu* display_inventory;
	int current_page;

	//Button to select which character to use the item on
	SelectCharacterForItem_Button* chara_select_btn[4];
	Menu* character_menu;

	//The item and and character to use it on
	Item* item_holder;
	CharacterInfo* chara_holder;
	int item_index;

	//prompts when button is used
	PopUp_Button* used_item;

	//utility buttons
	Menu* utilitybuttons;

	//initialise the buttons in the inventory
	void init_inventory();
};