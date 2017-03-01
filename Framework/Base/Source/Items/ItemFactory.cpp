#include "ItemFactory.h"

#include "Consumable.h"

Item* ItemFactory::CreateItem(string name)
{
	if (name == "Health Potion")
	{
		return new HealthPotion();
	}
	
	if (name == "Max Health Potion")
	{
		return new MaxHealthPotion();
	}
}