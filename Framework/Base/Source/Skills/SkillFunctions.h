#ifndef SKILL_FUNCTIONS_H
#define SKILL_FUNCTIONS_H

#include "../Entity/BattleEntity.h"
#include <vector>

using std::vector;

struct SkillParameters
{
	BattleEntity *caster;
	vector<BattleEntity*> *targetlist;
};

class SkillFunctions
{
public:
	static void Heal(SkillParameters *skillparam);
	static void Overpower(SkillParameters *skillparam);
};


#endif