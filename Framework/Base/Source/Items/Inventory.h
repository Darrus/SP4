#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include <Map>
#include <vector>

using std::map;
using std::vector;

#include <iostream>

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

	Inventory();
	~Inventory();
};


#endif INVENTORY_H