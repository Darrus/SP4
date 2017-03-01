#include "PartySystem.h"
#include "timer.h"
#include <iostream>
PartySystem::PartySystem() : 
currPartySize(0)
{
	for (int i = 0; i < maxPartySize; ++i)
	{
		party[i] = nullptr;
	}
}


PartySystem::~PartySystem()
{
}

CharacterInfo* PartySystem::GetMember(int id)
{
	for (int i = 0; i < maxPartySize; ++i)
	{
		if (party[i]->id == id)
			return party[i];
	}
}

bool PartySystem::AddMember(CharacterInfo* member)
{
	std::cout << "Adding... " << member->id << std::endl;
	for (int i = 0; i < maxPartySize; ++i)
	{
		if (party[i] == nullptr)
		{
			party[i] = member;
			std::cout << "Added!!" << member->id << std::endl;
			return true;
		}
	}
	std::cout << "Failed to add!! " << member->id << std::endl;
	return false;
}

CharacterInfo* PartySystem::RemoveMember(int id)
{
	for (int i = 0; i < maxPartySize; ++i)
	{
		if (party[i]->id == id)
		{
			CharacterInfo* result = party[i];
			party[i] = nullptr;
			return result;
		}
	}
}

CharacterInfo* PartySystem::RemoveMemberByIndex(int index)
{
	CharacterInfo* result = party[index];

	party[index] = nullptr;

	return result;
}

vector<CharacterInfo*> PartySystem::GetParty()
{
	vector<CharacterInfo*> partyVec;
	for (int i = 0; i < maxPartySize; ++i)
	{
		partyVec.push_back(party[i]);
	}
	return partyVec;
}

int PartySystem::memberCount()
{
    int count = 0;
    for (int i = 0; i < maxPartySize; ++i)
    {
		if (party[i] != nullptr)
			count++;
    }
    return count;
}