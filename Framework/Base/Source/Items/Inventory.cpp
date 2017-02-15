#include "Inventory.h"


Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}

void Inventory::AddItem(Item* itemToAdd)
{
	////If player does not have that item
	//if (m_inventoryMap.find("f") == m_inventoryMap.end())
	//{
	//	std::cout << "Player does not have this Item" << std::endl;
	//	
	//}
	//else 
	//{
	//	std::cout << "Player has this Item, adding to Stack instead" << std::endl;
	//}

	m_inventoryMap[itemToAdd->GetName()].push_back(itemToAdd);
	std::cout << "Added: " << itemToAdd->GetName() << ". Current stack size: " << m_inventoryMap[itemToAdd->GetName()].size() << std::endl;
}