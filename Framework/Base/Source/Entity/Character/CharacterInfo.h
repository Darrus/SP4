#ifndef CHARACTER_INFO_H
#define CHARACTER_INFO_H

#include <list>
#include <string>
#include "Stat.h"

using std::list;
using std::string;

class Skill;

typedef list<Skill*> SkillList;

struct CharacterInfo
{
	string name;
	SkillList skills;
	StatSystem stats;
	int HP;
	int MP;
};

#endif