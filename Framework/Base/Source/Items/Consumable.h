#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "Item.h"

//=================================================================================================//
//									  	  Abstract Base Class									   //
//=================================================================================================//
class Item;

class Consumable : public Item
{
protected:
	bool isEnemyTargetable;
	bool isAllyTargetable;

public:
	Consumable(){};
	~Consumable(){};

	//Virtual function when player uses the item
	virtual void UseOn(CharacterInfo* chara) = 0;

	//Getters and Setters
	inline bool CanTargetEnemy() { return isEnemyTargetable; }
	inline bool CanTargetAlly() { return isAllyTargetable; }
};

//=================================================================================================//
//									     	Item Classes										   //
//=================================================================================================//
class HealthPotion : public Consumable
{
private:
	int m_healValue;

public:
	void UseOn(CharacterInfo* chara);

	HealthPotion();
	~HealthPotion(){};
};

class MaxHealthPotion : public Consumable
{
private:

public:
	virtual void UseOn(CharacterInfo* chara);

	MaxHealthPotion();
	~MaxHealthPotion(){};
};

class ManaPotion : public Consumable
{
private:
	int m_mana_gain;

public:
	virtual void UseOn(CharacterInfo* chara);

	ManaPotion();
	~ManaPotion(){};
};

class MaxManaPotion : public Consumable
{
private:

public:
	virtual void UseOn(CharacterInfo* chara);

	MaxManaPotion();
	~MaxManaPotion(){};
};

// STAT POTIONS // 

class StrengthPotion : public Consumable
{
private:
	int m_str_increase_value;

public:
	virtual void UseOn(CharacterInfo* chara);

	StrengthPotion();
	~StrengthPotion(){};
};

class VitalityPotion : public Consumable
{
private:
	int m_vit_increase_value;

public:
	virtual void UseOn(CharacterInfo* chara);

	VitalityPotion();
	~VitalityPotion(){};
};

class IntelligencePotion : public Consumable
{
private:
	int m_int_increase_value;

public:
	virtual void UseOn(CharacterInfo* chara);

	IntelligencePotion();
	~IntelligencePotion(){};
};

class MindPotion : public Consumable
{
private:
	int m_mind_increase_value;

public:
	virtual void UseOn(CharacterInfo* chara);

	MindPotion();
	~MindPotion(){};
};

class DexterityPotion : public Consumable
{
private:
	int m_dex_increase_value;

public:
	virtual void UseOn(CharacterInfo* chara);

	DexterityPotion();
	~DexterityPotion(){};
};

class AgilityPotion : public Consumable
{
private:
	int m_agi_increase_value;

public:
	virtual void UseOn(CharacterInfo* chara);

	AgilityPotion();
	~AgilityPotion(){};
};

#endif