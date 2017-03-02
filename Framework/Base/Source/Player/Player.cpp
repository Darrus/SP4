#include <sstream>
#include "Player.h"

// Scene
#include "../Overworld/OverworldBase.h"

// Utilities
#include "../Lua/LuaInterface.h"
#include "SceneManager.h"
#include "../Character/CharacterFactory.h"

// Skills
#include "../Skills/SkillFunctions.h"
#include "..\Scenes\BattleState.h"


using std::stringstream;

Player::Player()
{
}


Player::~Player()
{

}

void Player::CopyInfo(SaveInfo* save)
{
	m_gold = save->m_gold;
	m_currentScene = save->GetScene();
	m_overworld_pos = save->GetOverworldPosition();
	
	vector<CharacterInfo*> partyVec = save->GetParty()->GetParty();
	for (int i = 0; i < m_party.GetMaxPartySize(); ++i)
		m_party.AddMember(partyVec[i], i);

	vector<Item*> itemVec = save->GetInventory()->GetItemList();
	for (int i = 0; i < itemVec.size(); ++i)
		m_inventory.AddItem(itemVec[i]);
}

void Player::Init()
{
	m_currentScene = "Overworld";
	m_overworld_pos = Vector3(0.f, 0.f, 0.f);
	m_gold = 100;
	m_party.AddMember(CharacterFactory::GetInstance()->CreateCharacter(5));
}