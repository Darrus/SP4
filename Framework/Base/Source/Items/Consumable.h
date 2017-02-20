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

#endif