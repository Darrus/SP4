#ifndef PARTY_SYSTEM_H
#define PARTY_SYSTEM_H

#include <vector>
#include "../Character/CharacterInfo.h"

using std::vector;

class PartySystem
{
	static const int maxPartySize = 4;
	CharacterInfo* party[maxPartySize];
    int currPartySize;
public:
	PartySystem();
	~PartySystem();

	CharacterInfo* GetMember(int id);
	CharacterInfo* GetMemberByIndex(int index){ return party[index]; }
	CharacterInfo* RemoveMember(int id);
	CharacterInfo* RemoveMemberByIndex(int index);

	vector<CharacterInfo*> GetParty();

	bool AddMember(CharacterInfo* member);
    int memberCount();

	inline int GetMaxPartySize() { return maxPartySize; }

    //void UpdateMemberInfo(CharacterInfo* info);
};

#endif