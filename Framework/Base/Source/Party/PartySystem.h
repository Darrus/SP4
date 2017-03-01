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
	CharacterInfo* RemoveMember(int id);

	vector<CharacterInfo*> GetParty();

	void AddMember(CharacterInfo* member);
    int memberCount();

	inline int GetMaxPartySize() { return maxPartySize; }

    //void UpdateMemberInfo(CharacterInfo* info);
};

#endif