#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Item.h"

enum EQUIPMENT_TYPE
{
	TYPE_WEAPON = 0,
	TYPE_ARMOUR,
	TYPE_ACCESSORY,

	NUM_EQUIPMENT_TYPE
};

class Equipment : public Item
{
protected:
	EQUIPMENT_TYPE m_type;

	//Weapon attributes
	int m_physical_dmg;
	int m_magic_dmg;

	//Armour and accessories attributes
	int m_physical_def;
	int m_magic_def;

public:

	//Getters and Setters
	inline EQUIPMENT_TYPE GetType() { return m_type; }

	inline int GetPhysicalDamage(){ return m_physical_dmg; }
	inline int GetMagicDamage(){ return m_magic_dmg; }

	inline int GetPhysicalDefense(){ return m_physical_def; }
	inline int GetMagicDefense(){ return m_magic_def; }

	//Equipment(){};
	Equipment(EQUIPMENT_TYPE type, int physDmg, int magicDmg, int physDef, int magicDef) : 
		m_type(type), m_physical_dmg(physDmg), m_magic_dmg(magicDmg), m_physical_def(physDef), m_magic_def(magicDef){};
	~Equipment(){};
};

#endif