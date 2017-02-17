#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "../Character/CharacterInfo.h"
//#include "Mesh.h"
#include "MeshBuilder.h"

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

	//To hold the image/icon of the item
	Mesh* m_icon;

public:
	//Getters and Setters
	inline string GetName() { return m_name; }
	inline void SetName(string name) { m_name = name; }

	inline string GetDescription() { return m_description; }
	inline void SetDescription(string desc) { m_description = desc; }

	inline void SetMesh(Mesh* mesh){ m_icon = mesh; }
	inline Mesh* GetMesh(){ return m_icon; }

	inline int GetGoldValue(){ return m_goldValue; }
	//inline void SetValue(int value){ m_value = value; } //Value shouldn't change

	Item() : m_name(""), m_description(""), m_goldValue(0), m_icon(MeshBuilder::GetInstance()->GetMesh("button_background")){}
	virtual ~Item(){}
};

#endif