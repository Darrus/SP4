#include "Consumable.h"
#include "MyMath.h"

//=================================================================================================//
//									  	  Health Potion											   //
//=================================================================================================//
HealthPotion::HealthPotion()
{
	Item();
	m_name = "Health Potion";
	m_healValue = Math::RandIntMinMax(0, 1000);
	m_goldValue = Math::RandIntMinMax(0, 1000);
	m_description = "Heals an ally character\nfor " + std::to_string(m_healValue) + " Health.";
	//m_icon = MeshBuilder::GetInstance()->GetMesh("potion");
}

void HealthPotion::UseOn(CharacterInfo* chara)
{
	chara->HP += m_healValue;
    chara->stats.UpdateStats();
}

//=================================================================================================//
//										Max Health Potion										   //
//=================================================================================================//
MaxHealthPotion::MaxHealthPotion()
{
	m_goldValue = Math::RandIntMinMax(0, 1000);
	m_name = "Max Health Potion";
	m_description = "Heals an Ally Character\nback to full health.";
	//m_icon = MeshBuilder::GetInstance()->GetMesh("max_potion");
}

void MaxHealthPotion::UseOn(CharacterInfo* chara)
{
	chara->HP = chara->stats.GetMaxHP();
     chara->stats.UpdateStats();
}