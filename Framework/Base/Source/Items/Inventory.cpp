#include "Inventory.h"
#include "Consumable.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"

#if INVENTORY_VERSION == 1

Inventory::Inventory()
{
}


Inventory::~Inventory()
{
	for (map<string, vector<Item*>>::iterator it = m_inventoryMap.begin(); it != m_inventoryMap.end();)
	{
		map<string, vector<Item*>>::iterator test = it;
		std::cout << "Erasing: " << it->first << ". Count: " << it->second.size() << std::endl;

		if (++test != m_inventoryMap.end())
		{
			m_inventoryMap.erase(it);
			it = test;
		}
		else
		{
			m_inventoryMap.erase(it);
			break;
		}
	}
}

void Inventory::AddItem(Item* itemToAdd)
{
	m_inventoryMap[itemToAdd->GetName()].push_back(itemToAdd);
	std::cout << "Added: " << itemToAdd->GetName() << ". Current stack size: " << m_inventoryMap[itemToAdd->GetName()].size() << std::endl;
}

void Inventory::PrintInventory()
{
	for (auto const& x : m_inventoryMap)
		std::cout << x.first << "| Count: " << x.second.size() << std::endl;
}

void Inventory::UseItem(int index, CharacterInfo* chara)
{
	//Probably don't need this
}

#endif

#if INVENTORY_VERSION == 2

Inventory::Inventory()
{
}


Inventory::~Inventory()
{
	for (auto it = m_inventoryList.begin(); it != m_inventoryList.end(); ++it)
		delete *it;
	
	m_inventoryList.clear();
}


void Inventory::AddItem(Item* itemToAdd)
{
	m_inventoryList.push_back(itemToAdd);
}

bool Inventory::UseItem(int index, CharacterInfo* chara)
{
	//Check if the item is a consumable
	Consumable* cnsmble = dynamic_cast<Consumable*>(m_inventoryList[index]);

	//Returns false if it's not a consumable
	if (cnsmble == nullptr)
		return false;
	else
	{
		//Use the item and remove it after
		cnsmble->UseOn(chara);
		m_inventoryList.erase(m_inventoryList.begin() + index);
		return true;
	}
}

void Inventory::PrintInventory()
{
	std::cout << "Inventory has " << m_inventoryList.size() << " items."<< std::endl << "=============================================================" << std::endl;

	for (unsigned i = 0; i < m_inventoryList.size(); ++i)
		std::cout << i + 1 << ": " << m_inventoryList[i]->GetName() << " -> " << m_inventoryList[i]->GetDescription() << std::endl;
}

void Inventory::RenderItem(int index, float pos_x, float pos_y, float scale_x, float scale_y)
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(pos_x, pos_y, 0);
	modelStack.PushMatrix();
	modelStack.Scale(scale_x, scale_y, 1);
	RenderHelper::RenderMesh(m_inventoryList[index]->GetMesh());
	modelStack.PopMatrix();
	modelStack.Translate(-scale_x * 0.5f, 0, 0);
	modelStack.Scale(20, 20, 1);
	RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), m_inventoryList[index]->GetName(), Color(1, 0, 0));
	modelStack.PopMatrix();
}

#endif