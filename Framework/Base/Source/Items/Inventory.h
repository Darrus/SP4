#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include "../Character/CharacterInfo.h"
#include <Map>
#include <vector>
#include <List>

#define INVENTORY_VERSION 2

using std::map;
using std::vector;

#include <iostream>

#if INVENTORY_VERSION == 1

class Inventory
{
private:
	//Using a Map to store inventory.
	//Item's name as Map Key 
	//Int as counter for the amount of items the player has

public:

	//HACK
	map<string, vector<Item*>> m_inventoryMap;

	void AddItem(Item* itemToAdd);
	void UseItem(int index, CharacterInfo* chara);
	void PrintInventory();

	Inventory();
	~Inventory();
};

#endif

#if INVENTORY_VERSION == 2
class Inventory
{
private:

public:
	//HACK:
	vector<Item*> m_inventoryList;

	void AddItem(Item* itemToAdd);
	bool UseItem(int index, CharacterInfo* chara);
	void PrintInventory();

	void RenderItem(int index, float pos_x, float pos_y, float scale_x, float scale_y);

	Inventory();
	~Inventory();
};
#endif

#endif INVENTORY_H