#include "Inventory.h"
#include "Consumable.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"

Inventory::Inventory()
{
}


Inventory::~Inventory()
{
	ClearInventory();
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

void Inventory::ClearInventory()
{
	for (auto it = m_inventoryList.begin(); it != m_inventoryList.end(); ++it)
		delete *it;

	m_inventoryList.clear();
}