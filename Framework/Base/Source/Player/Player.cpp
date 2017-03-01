#include <sstream>
#include "Player.h"

// Scene
#include "../Overworld/OverworldBase.h"

// Utilities
#include "../Lua/LuaInterface.h"
#include "SceneManager.h"

// Skills
#include "../Skills/SkillFunctions.h"

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
	// Load Player Info
	string fileLoc = "Savefiles//" + fileName + "//PlayerInfo";
	Lua->LoadFile(fileLoc);
	Lua->SaveStringValue(fileLoc.c_str(), "Scene", SceneManager::GetInstance()->GetActiveSceneName().c_str(), true);
	for (int i = 0; i < m_party.GetMaxPartySize(); ++i)
	{
		SaveCharacter(fileName, i);
	}
	//Lua->SaveVector3Values(fileLoc.c_str(), "Position", SceneManager::GetInstance()->GetActiveScene(), true);
}

void Player::SaveCharacter(string fileName, int index)
{
	stringstream fileLoc;
	fileLoc << "Savefiles//" << fileName << "//Character" << index + 1;
	CharacterInfo* character = m_party.GetParty() + index;
	if (!character)
		return;

	Lua->SaveStringValue(fileLoc.str().c_str(), "Name", character->name.c_str(), true);
	Lua->SaveIntValue(fileLoc.str().c_str(), "Str", character->stats.GetStr());
	Lua->SaveIntValue(fileLoc.str().c_str(), "Vit", character->stats.GetVit());
	Lua->SaveIntValue(fileLoc.str().c_str(), "Int", character->stats.GetInt());
	Lua->SaveIntValue(fileLoc.str().c_str(), "Mind", character->stats.GetMind());
	Lua->SaveIntValue(fileLoc.str().c_str(), "Dex", character->stats.GetDex());
	Lua->SaveIntValue(fileLoc.str().c_str(), "Agi", character->stats.GetAgi());
	Lua->SaveIntValue(fileLoc.str().c_str(), "StatPoint", character->stats.GetStatPoints());
	Lua->SaveIntValue(fileLoc.str().c_str(), "SkillPoint", character->stats.GetSkillPoints());
}

void Player::LoadGame(string fileName)
{
	// Load Player Info
	string fileLoc = "Savefiles//" + fileName + "//PlayerInfo";
	Lua->LoadFile(fileLoc);

	string sceneName = Lua->GetStringValue("Scene");
	Vector3 position = Lua->GetVector3Values("Position");
	//OverworldBase* scene = dynamic_cast<OverworldBase*>(SceneManager::GetInstance()->SetActiveScene(sceneName));
	//scene->SetStartPos(position);

	// Load Party Info
	//for (int i = 0; i < m_party.GetMaxPartySize(); ++i)
	//{
		LoadCharacter(fileName, 1);
	//}
}

CharacterInfo* Player::LoadCharacter(string fileName, int index)
{
	// Load Character Info
	CharacterInfo* character = nullptr;
	stringstream fileLoc;

	fileLoc << "Savefiles//" << fileName << "//Character" << index;
	if (Lua->LoadFile(fileLoc.str()))
	{
		character = new CharacterInfo();
		character->name = Lua->GetStringValue("Name");
		character->stats.AddLevel(Lua->GetIntValue("Level"));
		character->stats.AddStr(Lua->GetIntValue("Str"));
		character->stats.AddVit(Lua->GetIntValue("Vit"));
		character->stats.AddInt(Lua->GetIntValue("Int"));
		character->stats.AddMind(Lua->GetIntValue("Mind"));
		character->stats.AddDex(Lua->GetIntValue("Dex"));
		character->stats.AddAgi(Lua->GetIntValue("Agi"));
		character->stats.AddStatPoint(Lua->GetIntValue("StatPoint"));
		character->stats.AddSkillPoint(Lua->GetIntValue("SkillPoint"));

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