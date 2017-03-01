#pragma once

#include <string>

class Item;

using std::string;

class ItemFactory
{
public:
	static Item* CreateItem(string name);
};

