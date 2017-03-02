#pragma once

#include <string>
#include <vector>

#include "CharacterInfo.h"
#include "SingletonTemplate.h"

using std::string;
using std::vector;

class CharacterFactory : public Singleton<CharacterFactory>
{
private:
	vector<string> names;
	void RandomStat(CharacterInfo* character);

public:
	friend Singleton<CharacterFactory>;

	CharacterFactory();
	~CharacterFactory();

	CharacterInfo* CreateCharacter();
};

