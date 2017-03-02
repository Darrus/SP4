#include <sstream>
#include "SaveInfo.h"

// Scene
#include "../Overworld/OverworldBase.h"

// Utilities
#include "../Lua/LuaInterface.h"
#include "SceneManager.h"
#include "../Items/ItemFactory.h"
#include "../Character/CharacterFactory.h"

// Skills
#include "../Skills/SkillFunctions.h"
#include "..\Scenes\BattleState.h"

using std::stringstream;

SaveInfo::SaveInfo()
{
}


SaveInfo::~SaveInfo()
{

}
void SaveInfo::DoDie()
{
	//TODO:
	//Most likely goto "You Died" scene and return to main menu to save
}

bool SaveInfo::SaveGame(string fileName)
{
	// Save SaveInfo Info
	OverworldBase* scene = dynamic_cast<OverworldBase*>(SceneManager::GetInstance()->GetActiveScene());
	string fileLoc = "Savefiles//" + fileName + "//PlayerInfo";
	if (!Lua->LoadFile(fileLoc))
		return false;
	
	Lua->SaveStringValue(fileLoc.c_str(), "Scene", SceneManager::GetInstance()->GetActiveSceneName().c_str(), true);
	Lua->SaveVector3Values(fileLoc.c_str(), "Position", scene->GetPlayerPos());
	Lua->SaveIntValue(fileLoc.c_str(), "Gold", m_gold);

	// Save Party
	vector<CharacterInfo*> partyVec = m_party.GetParty();
	for (int i = 0; i < partyVec.size(); ++i)
	{
		if (partyVec[i])
			SaveCharacter(fileName, partyVec[i], i);
	}

	// Save Inventory
	fileLoc = "Savefiles//" + fileName + "//Inventory";
	vector<Item*> itemList = m_inventory.GetItemList();
	string itemNames;
	for (int i = 0; i < itemList.size(); ++i)
	{
		itemNames += ("\"" + itemList[i]->GetName() + ",\n");
	}
	if (itemNames != "")
	{
		itemNames.pop_back();
		itemNames.pop_back();
	}
	Lua->SaveStringTable(fileLoc.c_str(), "Inventory", itemNames.c_str(), true);

	// Save Events
	fileLoc = "Savefiles//" + fileName + "//Events";
	Lua->SaveBoolTable(fileLoc.c_str(), "Events", eventSystem.events, Events::NUM_EVENTS, true);
	return true;
}

void SaveInfo::SaveCharacter(string fileName, CharacterInfo* character, int index)
{
	stringstream fileLoc;
	fileLoc << "Savefiles//" << fileName << "//Character" << index + 1;
	Lua->SaveStringValue(fileLoc.str().c_str(), "Name", character->name.c_str(), true);
    Lua->SaveIntValue(fileLoc.str().c_str(), "Level", character->stats.Getlevel());
	Lua->SaveIntValue(fileLoc.str().c_str(), "Str", character->stats.GetStr());
	Lua->SaveIntValue(fileLoc.str().c_str(), "Vit", character->stats.GetVit());
	Lua->SaveIntValue(fileLoc.str().c_str(), "Int", character->stats.GetInt());
	Lua->SaveIntValue(fileLoc.str().c_str(), "Mind", character->stats.GetMind());
	Lua->SaveIntValue(fileLoc.str().c_str(), "Dex", character->stats.GetDex());
	Lua->SaveIntValue(fileLoc.str().c_str(), "Agi", character->stats.GetAgi());
	Lua->SaveIntValue(fileLoc.str().c_str(), "StatPoint", character->stats.GetStatPoints());
	Lua->SaveIntValue(fileLoc.str().c_str(), "SkillPoint", character->stats.GetSkillPoints());
	Lua->SaveIntValue(fileLoc.str().c_str(), "HP", character->HP);
	Lua->SaveIntValue(fileLoc.str().c_str(), "MP", character->MP);
	Lua->SaveIntValue(fileLoc.str().c_str(), "EXP", character->EXP);
	Lua->SaveIntValue(fileLoc.str().c_str(), "BRANCH_P_ATK", character->skill_branch_index[BRANCH_P_ATK]);
	Lua->SaveIntValue(fileLoc.str().c_str(), "BRANCH_M_ATK", character->skill_branch_index[BRANCH_M_ATK]);
	Lua->SaveIntValue(fileLoc.str().c_str(), "BRANCH_P_DEF", character->skill_branch_index[BRANCH_P_DEF]);
	Lua->SaveIntValue(fileLoc.str().c_str(), "BRANCH_P_DEF", character->skill_branch_index[BRANCH_M_DEF]);


	CharacterInfo::SkillList::iterator it = character->skills.begin();
	string skillNames;
	while (it != character->skills.end())
	{
		skillNames += ("\"" + (*it)->GetName() + "\",\n");
		it++;
	}

	if (skillNames != "")
	{
		skillNames.pop_back();
		skillNames.pop_back();
	}

	Lua->SaveStringTable(fileLoc.str().c_str(), "Skills", skillNames.c_str());
}

bool SaveInfo::LoadGame(string fileName)
{
	// Load SaveInfo Info
	string fileLoc = "Savefiles//" + fileName + "//PlayerInfo";
	Lua->LoadFile(fileLoc);
	Lua->DoActiveState();

	m_currentScene = Lua->GetStringValue("Scene");

	if (m_currentScene == "")
		return false;

	m_overworld_pos = Lua->GetVector3Values("Position");

	// Load Party Info
	for (int i = 0; i < (m_party.GetMaxPartySize()); ++i)
	{
		m_party.AddMember(LoadCharacter(fileName, i), i);
	}

	// Load Inventory
	fileLoc = "Savefiles//" + fileName + "//Inventory";
	Lua->LoadFile(fileLoc);
	vector<string> itemNames = Lua->GetStringTable("Inventory");
	while (itemNames.size() > 0)
	{
		m_inventory.AddItem(ItemFactory::CreateItem(itemNames.back()));
		itemNames.pop_back();
	}

	// Load Events
	fileLoc = "Savefiles//" + fileName + "//Events";
	Lua->LoadFile(fileLoc);
	vector<bool> eventVec = Lua->GetBoolTable("Events");
	int i = 0;
	while (eventVec.size() > 0)
	{
		eventSystem.events[i] = eventVec.back();
		eventVec.pop_back();
	}

	return true;
}

CharacterInfo* SaveInfo::LoadCharacter(string fileName, int index)
{
	// Load Character Info
	CharacterInfo* character = nullptr;
	stringstream fileLoc;

	fileLoc << "Savefiles//" << fileName << "//Character" << (index + 1);
	if (Lua->LoadFile(fileLoc.str()))
	{
		string name = Lua->GetStringValue("Name");

		if (name == "")
		{
			return nullptr;
		}

		character = CharacterFactory::GetInstance()->GetCharacter(name);
		character->stats.AddLevel(Lua->GetIntValue("Level"));
		character->stats.SetStr(Lua->GetIntValue("Str"));
		character->stats.SetVit(Lua->GetIntValue("Vit"));
		character->stats.SetInt(Lua->GetIntValue("Int"));
		character->stats.SetMind(Lua->GetIntValue("Mind"));
		character->stats.SetDex(Lua->GetIntValue("Dex"));
		character->stats.SetAgi(Lua->GetIntValue("Agi"));
		character->HP = Lua->GetIntValue("HP");
		character->MP = Lua->GetIntValue("MP");
		character->EXP = Lua->GetIntValue("EXP");
		character->id = CharacterFactory::GetInstance()->GenerateID();
		character->stats.SetStatPoint(Lua->GetIntValue("StatPoint"));
		character->stats.SetSkillPoint(Lua->GetIntValue("SkillPoint"));
		character->stats.UpdateStats();

		character->HP = character->stats.GetMaxHP();
		character->MP = character->stats.GetMaxMP();

		character->skill_branch_index[BRANCH_P_ATK] = Lua->GetIntValue("BRANCH_P_ATK");
		character->skill_branch_index[BRANCH_M_ATK] = Lua->GetIntValue("BRANCH_M_ATK");
		character->skill_branch_index[BRANCH_P_DEF] = Lua->GetIntValue("BRANCH_P_DEF");
		character->skill_branch_index[BRANCH_M_DEF] = Lua->GetIntValue("BRANCH_M_DEF");

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