#include "Consumable.h"

//========================================//
// TODO:								  //
// Load item values from text file / lua  //
//========================================//


//=================================================================================================//
//									  	  Health Potion											   //
//=================================================================================================//
HealthPotion::HealthPotion()
{
	m_healValue = 50;
	m_goldValue = 10;
	m_name = "Health Potion";
	m_description = "Heals an Ally Character for " + std::to_string(m_healValue) + " health.";
}

void HealthPotion::UseOn(CharacterInfo* chara)
{
	chara->HP += m_healValue;
}

//=================================================================================================//
//										Max Health Potion										   //
//=================================================================================================//
MaxHealthPotion::MaxHealthPotion()
{
	m_goldValue = 500;
	m_name = "Max Health Potion";
	m_description = "Heals an Ally Character to full health.";
}

void MaxHealthPotion::UseOn(CharacterInfo* chara)
{
	//TODO Waiting for Darrus to change character info main/sub stat stuff

	//chara->HP = chara->stats.GetMaxHP();
}