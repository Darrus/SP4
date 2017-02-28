#ifndef PLAYER_H
#define PLAYER_H

#include "../Party/PartySystem.h"
#include "../Items/Inventory.h"
#include "../../Common/Source/Vector3.h";

class Player
{
private:
	PartySystem m_party;
	int m_gold;
	Inventory m_inventory;
	string m_currentScene;
	int m_hours, m_mins;
	//float m_overworld_pos_x, m_overworld_pos_y;
	Vector3 m_overworld_pos;

	//TODO:
	CharacterInfo* LoadCharacter(string fileName, int index);
	void SaveCharacter(string fileName, int index);
	//Store a respawnpoint?

public:
	static Player& GetInstance()
	{
		static Player player;
		return player;
	}

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
    inline void SetParty(PartySystem party) { m_party = party;  }

    inline Inventory* GetInventory() { return &m_inventory; }
    inline void SetInventory(Inventory inventory) { m_inventory = inventory; }

	Player();
	~Player();
};

#endif