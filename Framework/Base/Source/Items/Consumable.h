#ifndef CONSUMABLE_H
#define CONSUMABLE_H

#include "Item.h"

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
	virtual void UseOn() = 0;

	//Getters and Setters
	inline bool CanTargetEnemy() { return isEnemyTargetable; }
	inline bool CanTargetAlly() { return isAllyTargetable; }
};

class HealthPotion : public Consumable
{
private:
	int m_healValue;

public:
	virtual void UseOn();

	HealthPotion();
	~HealthPotion(){};
};


class MaxHealthPotion : public Consumable
{
private:

public:
	virtual void UseOn();

	MaxHealthPotion();
	~MaxHealthPotion(){};
};

#endif