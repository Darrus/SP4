#include "Consumable.h"

HealthPotion::HealthPotion()
{
	//TODO: 
	//Load these values from text file / lua

	m_healValue = 50;
	m_goldValue = 10;
	m_name = "Health Potion";
	m_description = "Heals an Ally Character for " + std::to_string(m_healValue) + " health.";
}

void HealthPotion::UseOn()
{
	//TODO: 
	//Pass in character entity in here.
	//Do potion logic here. 
}

MaxHealthPotion::MaxHealthPotion()
{
	//TODO: 
	//Load these values from text file / lua

	m_goldValue = 500;
	m_name = "Max Health Potion";
	m_description = "Heals an Ally Character to full health.";
}

void MaxHealthPotion::UseOn()
{
	//TODO: 
	//Pass in character entity in here.
	//Do potion logic here. 
}