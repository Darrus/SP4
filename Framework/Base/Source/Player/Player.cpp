#include <sstream>
#include "Player.h"

// Scene
#include "../Overworld/OverworldBase.h"

// Utilities
#include "../Lua/LuaInterface.h"
#include "SceneManager.h"

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
void Player::DoDie()
{
	//TODO:
	//Most likely goto "You Died" scene and return to main menu to save
}

void Player::SaveGame(string fileName)
{
	// Save Player Info
	OverworldBase* scene = dynamic_cast<OverworldBase*>(SceneManager::GetInstance()->GetActiveScene());
	string fileLoc = "Savefiles//" + fileName + "//PlayerInfo";
	Lua->LoadFile(fileLoc);
	Lua->SaveStringValue(fileLoc.c_str(), "Scene", SceneManager::GetInstance()->GetActiveSceneName().c_str(), true);
	Lua->SaveVector3Values(fileLoc.c_str(), "Position", scene->GetPlayerPos());
	Lua->SaveIntValue(fileLoc.c_str(), "Gold", m_gold);
	
	vector<CharacterInfo*> partyVec = m_party.GetParty();

	for (int i = 0; i < partyVec.size(); ++i)
	{
		if (partyVec[i])
			SaveCharacter(fileName, partyVec[i], i);
	}
}

void Player::SaveCharacter(string fileName, CharacterInfo* character, int index)
{
	stringstream fileLoc;
	fileLoc << "Savefiles//" << fileName << "//Character" << index + 1;
	Lua->SaveStringValue(fileLoc.str().c_str(), "Name", character->name.c_str(), true);
	Lua->SaveIntValue(fileLoc.str().c_str(), "Str", character->stats.GetStr());
	Lua->SaveIntValue(fileLoc.str().c_str(), "Vit", character->stats.GetVit());
	Lua->SaveIntValue(fileLoc.str().c_str(), "Int", character->stats.GetInt());
	Lua->SaveIntValue(fileLoc.str().c_str(), "Mind", character->stats.GetMind());
	Lua->SaveIntValue(fileLoc.str().c_str(), "Dex", character->stats.GetDex());
	Lua->SaveIntValue(fileLoc.str().c_str(), "Agi", character->stats.GetAgi());
	Lua->SaveIntValue(fileLoc.str().c_str(), "StatPoint", character->stats.GetStatPoints());
	Lua->SaveIntValue(fileLoc.str().c_str(), "SkillPoint", character->stats.GetSkillPoints());

	CharacterInfo::SkillList::iterator it = character->skills.begin();
	string skillNames;
	while (it != character->skills.end())
	{
		skillNames += ("\"" + (*it)->GetName() + "\", ");
		it++;
	}

	skillNames.pop_back();
	skillNames.pop_back();

	Lua->SaveStringTable(fileLoc.str().c_str(), "Skills", skillNames.c_str());
}

void Player::LoadGame(string fileName)
{
	// Load Player Info
	string fileLoc = "Savefiles//" + fileName + "//PlayerInfo";
	Lua->LoadFile(fileLoc);

	string sceneName = Lua->GetStringValue("Scene");
	Vector3 position = Lua->GetVector3Values("Position");
	OverworldBase* scene = dynamic_cast<OverworldBase*>(SceneManager::GetInstance()->SetActiveScene(sceneName));
	scene->SetStartPos(position);
    
	// Load Party Info
	for (int i = 0; i < (m_party.GetMaxPartySize()); ++i)
	{
        m_party.AddMember(LoadCharacter(fileName, i));

	}
}

CharacterInfo* Player::LoadCharacter(string fileName, int index)
{
	// Load Character Info
	CharacterInfo* character = nullptr;
	stringstream fileLoc;

	fileLoc << "Savefiles//" << fileName << "//Character" << (index + 1);
	if (Lua->LoadFile(fileLoc.str()))
	{
		character = new CharacterInfo();
		character->name = Lua->GetStringValue("Name");
		
		if (character->name == "")
		{
			delete character;
			return nullptr;
		}

		character->stats.AddLevel(Lua->GetIntValue("Level"));
		character->stats.SetStr(Lua->GetIntValue("Str"));
		character->stats.SetVit(Lua->GetIntValue("Vit"));
		character->stats.SetInt(Lua->GetIntValue("Int"));
		character->stats.SetMind(Lua->GetIntValue("Mind"));
		character->stats.SetDex(Lua->GetIntValue("Dex"));
		character->stats.SetAgi(Lua->GetIntValue("Agi"));
        character->id = index;
		character->stats.SetStatPoint(Lua->GetIntValue("StatPoint"));
		character->stats.SetSkillPoint(Lua->GetIntValue("SkillPoint"));
        character->stats.UpdateStats();
        character->HP = character->stats.GetMaxHP();
        character->MP = character->stats.GetMaxMP();

		vector<string> skillNames = Lua->GetStringTable("Skills");
		while (skillNames.size() > 0)
		{
			string name = skillNames.back();
			character->skills.push_back(SkillContainer::GetInstance()->GetSkill(name));
			skillNames.pop_back();
		}
	}
	return character;
}

void Player::Init()
{
	m_gold = 1000000;
}