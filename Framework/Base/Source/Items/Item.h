#ifndef ITEM_H
#define ITEM_H

#include <string>

using std::string;

class Item
{
protected:
	//Name of the item
	string m_name;

	//Description of the item
	string m_description;

	//Gold value of the item
	int m_goldValue;

public:
	//Getters and Setters
	inline string GetName() { return m_name; }
	inline void SetName(string name) { m_name = name; }

	inline string GetDescription() { return m_description; }
	inline void SetDescription(string desc) { m_description = desc; }

	inline int GetGoldValue(){ return m_goldValue; }
	//inline void SetValue(int value){ m_value = value; } //Value shouldn't change

	Item() : m_name(""), m_description(""), m_goldValue(0){}
	virtual ~Item(){}
};

#endif