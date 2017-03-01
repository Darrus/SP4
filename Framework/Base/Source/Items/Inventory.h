#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include "../Character/CharacterInfo.h"
#include <Map>
#include <vector>
#include <List>

using std::map;
using std::vector;

#include <iostream>

class Inventory
{
private:

public:
	//HACK:
	vector<Item*> m_inventoryList;

	void AddItem(Item* itemToAdd);
	void AddCopy(Item* itemToCopy);
	bool UseItem(int index, CharacterInfo* chara);
	void PrintInventory();

	void RenderItem(int index, float pos_x, float pos_y, float scale_x, float scale_y);
	void ClearInventory();

	inline vector<Item*> GetItemList() { return m_inventoryList; }

	Inventory();
	~Inventory();
};

#endif INVENTORY_H