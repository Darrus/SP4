#pragma once

#include "../Party/PartySystem.h"
#include "../Items/Inventory.h"
#include "Events.h"
#include "Vector3.h"

class SaveInfo
{
protected:
	PartySystem m_party;
	Inventory m_inventory;
	string m_currentScene;
	Vector3 m_overworld_pos;

	CharacterInfo* LoadCharacter(string fileName, int index);
	void SaveCharacter(string fileName, CharacterInfo* character, int index);

public:
	int m_gold;
	Events eventSystem;

	//Helper functions
	void DoDie();
	void SaveGame(string fileName);
	void LoadGame(string fileName);

	void Init();
	void Update();

	//Getters and Setters
	inline Vector3 GetOverworldPosition() { return m_overworld_pos; };
	inline void SetOverworldPosition(Vector3 pos) { m_overworld_pos = pos; };

	inline PartySystem* GetParty() { return &m_party; }
	inline void SetParty(PartySystem party) { m_party = party; }

	inline Inventory* GetInventory() { return &m_inventory; }
	inline void SetInventory(Inventory inventory) { m_inventory = inventory; }

	inline void SetScene(string scene) { m_currentScene = scene; }
	inline string GetScene() { return m_currentScene; }

	SaveInfo();
	virtual ~SaveInfo();
};
