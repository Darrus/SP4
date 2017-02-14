#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Item.h"

class Equipment : public Item
{
public:
	enum EQUIPMENT_TYPE
	{
		TYPE_WEAPON = 0,
		TYPE_ARMOUR,
		TYPE_ACCESSORY,

		NUM_EQUIPMENT_TYPE
	};

protected:
	EQUIPMENT_TYPE m_type;

public:

	//Getters and Setters
	inline EQUIPMENT_TYPE GetType() { return m_type; }
	//inline void SetType(EQUIPMENT_TYPE type) { m_type = type; } //Type technically not supposed to be change

	Equipment();
	~Equipment();
};

#endif