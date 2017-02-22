#ifndef PARTY_SYSTEM_H
#define PARTY_SYSTEM_H

#include "../Character/CharacterInfo.h"

class PartySystem
{
	static const size_t maxPartySize = 4;
	CharacterInfo* party[maxPartySize];
    int currPartySize;
public:
	PartySystem();
	~PartySystem();

	CharacterInfo* GetMember(int id);
	CharacterInfo* RemoveMember(int id);
	void AddMember(CharacterInfo* member);
    int memberCount();
    //void UpdateMemberInfo(CharacterInfo* info);
};

#endif