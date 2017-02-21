#include "PartySystem.h"
#include "timer.h"

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

void PartySystem::AddMember(CharacterInfo* member)
{
	for (int i = 0; i < maxPartySize; ++i)
	{
		if (party[i] == nullptr)
		{
			party[i] = member;
			break;
		}
	}
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

int PartySystem::memberCount()
{
    int count = 0;
    for (int i = 0; i < maxPartySize; ++i)
    {
        count++;
    }
    return count;
}