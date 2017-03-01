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

public:
	friend Singleton<CharacterFactory>;

	void Init();
	CharacterInfo* CreateCharacter(string name);
};

