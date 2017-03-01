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
	m_goldValue = m_healValue * 20;
	m_description = "Restores an Ally Character\'s\nhealth by " + std::to_string(m_healValue);
	m_icon = MeshBuilder::GetInstance()->GetMesh("health_potion");
}

void HealthPotion::UseOn(CharacterInfo* chara)
{
	if (chara->stats.GetMaxHP() <= chara->HP + m_healValue)
		chara->HP = chara->stats.GetMaxHP();
	else
		chara->HP += m_healValue;

	//TODO: Do I need to update stats for this?
    chara->stats.UpdateStats();
}

//=================================================================================================//
//										Max Health Potion										   //
//=================================================================================================//
MaxHealthPotion::MaxHealthPotion()
{
	m_goldValue = 1000;
	m_name = "Max Health Potion";
	m_description = "Restores an Ally Character\nto full health.";
	m_icon = MeshBuilder::GetInstance()->GetMesh("max_health_potion");
}


void MaxHealthPotion::UseOn(CharacterInfo* chara)
{
	chara->HP = chara->stats.GetMaxHP();
     chara->stats.UpdateStats();
}

//=================================================================================================//
//											Mana Potion											   //
//=================================================================================================//
ManaPotion::ManaPotion()
{
	m_mana_gain = 20;
	m_goldValue = m_mana_gain * 20;
	m_name = "Mana Potion";
	m_description = "Restore an Ally Character\'s\nmana by" + std::to_string(m_mana_gain);
	m_icon = MeshBuilder::GetInstance()->GetMesh("mana_potion");
}

void ManaPotion::UseOn(CharacterInfo* chara)
{
	if (chara->stats.GetMaxMP() <= chara->MP + m_mana_gain)
		chara->MP = chara->stats.GetMaxHP();
	else
		chara->MP += m_mana_gain;
}

//=================================================================================================//
//										Max Mana Potion											   //
//=================================================================================================//
MaxManaPotion::MaxManaPotion()
{
	m_goldValue = 2000;
	m_name = "Max Mana Potion";
	m_description = "Restore an Ally Character\nto full mana.";
	m_icon = MeshBuilder::GetInstance()->GetMesh("max_mana_potion");
}


void MaxManaPotion::UseOn(CharacterInfo* chara)
{
	chara->MP = chara->stats.GetMaxMP();
	chara->stats.UpdateStats();
}

//=================================================================================================//
//										Strength Potion											   //
//=================================================================================================//
StrengthPotion::StrengthPotion()
{
	m_str_increase_value = 10;
	m_goldValue = m_str_increase_value * 500;
	m_name = "Strength Potion";
	m_description = "An Ally Character gains\n" + std::to_string(m_str_increase_value) + " STR permanently"; 
	m_icon = MeshBuilder::GetInstance()->GetMesh("stat_potion");
}

void StrengthPotion::UseOn(CharacterInfo* chara)
{
	chara->stats.AddStr(m_str_increase_value);
	chara->stats.UpdateStats();
}

//=================================================================================================//
//										Vitality Potion											   //
//=================================================================================================//
VitalityPotion::VitalityPotion()
{
	m_vit_increase_value = 10;
	m_goldValue = m_vit_increase_value * 500;
	m_name = "Vitality Potion";
	m_description = "An Ally Character gains\n" + std::to_string(m_vit_increase_value) + " VIT permanently";
	m_icon = MeshBuilder::GetInstance()->GetMesh("stat_potion");
}

void VitalityPotion::UseOn(CharacterInfo* chara)
{
	chara->stats.AddVit(m_vit_increase_value);
	chara->stats.UpdateStats();
}

//=================================================================================================//
//										Strength Potion											   //
//=================================================================================================//
IntelligencePotion::IntelligencePotion()
{
	m_int_increase_value = 10;
	m_goldValue = m_int_increase_value * 500;
	m_name = "Intelligence Potion";
	m_description = "An Ally Character gains\n" + std::to_string(m_int_increase_value) + " INT permanently";
	m_icon = MeshBuilder::GetInstance()->GetMesh("stat_potion");
}

void IntelligencePotion::UseOn(CharacterInfo* chara)
{
	chara->stats.AddInt(m_int_increase_value);
	chara->stats.UpdateStats();
}

//=================================================================================================//
//											Mind Potion											   //
//=================================================================================================//
MindPotion::MindPotion()
{
	m_mind_increase_value = 10;
	m_goldValue = m_mind_increase_value * 500;
	m_name = "Mind Potion";
	m_description = "An Ally Character gains\n" + std::to_string(m_mind_increase_value) + " MIND permanently";
	m_icon = MeshBuilder::GetInstance()->GetMesh("stat_potion");
}

void MindPotion::UseOn(CharacterInfo* chara)
{
	chara->stats.AddMind(m_mind_increase_value);
	chara->stats.UpdateStats();
}

//=================================================================================================//
//										Dexterity Potion										   //
//=================================================================================================//
DexterityPotion::DexterityPotion()
{
	m_dex_increase_value = 10;
	m_goldValue = m_dex_increase_value * 500;
	m_name = "Dexterity Potion";
	m_description = "An Ally Character gains\n" + std::to_string(m_dex_increase_value) + " DEX permanently";
	m_icon = MeshBuilder::GetInstance()->GetMesh("stat_potion");
}

void DexterityPotion::UseOn(CharacterInfo* chara)
{
	chara->stats.AddStr(m_dex_increase_value);
	chara->stats.UpdateStats();
}

//=================================================================================================//
//										Agility Potion											   //
//=================================================================================================//
AgilityPotion::AgilityPotion()
{
	m_agi_increase_value = 10;
	m_goldValue = m_agi_increase_value * 500;
	m_name = "Agility Potion";
	m_description = "An Ally Character gains\n" + std::to_string(m_agi_increase_value) + " AGI permanently";
	m_icon = MeshBuilder::GetInstance()->GetMesh("stat_potion");
}

void AgilityPotion::UseOn(CharacterInfo* chara)
{
	chara->stats.AddStr(m_agi_increase_value);
	chara->stats.UpdateStats();
}