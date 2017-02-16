#include "Consumable.h"
#include "MyMath.h"
//========================================//
// TODO:								  //
// Load item values from text file / lua  //
//========================================//


//=================================================================================================//
//									  	  Health Potion											   //
//=================================================================================================//
HealthPotion::HealthPotion()
{
	m_name = "Health Potion";
	m_healValue = Math::RandIntMinMax(50,100);//50;
	m_goldValue = 10;
	m_description = "HEALS AN ALLY CHARACTER FOR " + std::to_string(m_healValue) + " HEALTH.";
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
	m_description = "Heals an Ally Character back to full health.";
}

void MaxHealthPotion::UseOn(CharacterInfo* chara)
{
	chara->HP = chara->stats.GetMaxHP();
}