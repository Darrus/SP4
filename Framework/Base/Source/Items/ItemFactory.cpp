#include "ItemFactory.h"

#include "Consumable.h"

Item* ItemFactory::CreateItem(string name)
{
	if (name == "Health Potion")
		return new HealthPotion();
	if (name == "Max Health Potion")
		return new MaxHealthPotion();
	if (name == "Mana Potion")
		return new ManaPotion();
	if (name == "Max Mana Potion")
		return new MaxManaPotion();
	if (name == "Strength Potion")
		return new StrengthPotion;
	if (name == "Vitility Potion")
		return new VitalityPotion;
	if (name == "Intelligence Potion")
		return new IntelligencePotion;
	if (name == "Mind Potion")
		return new MindPotion;
	if (name == "Agility Potion")
		return new AgilityPotion;
	if (name == "Dexterity Potion")
		return new DexterityPotion;
}