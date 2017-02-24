#ifndef CHARACTER_INFO_H
#define CHARACTER_INFO_H

#define STAT_POINT_GAIN 5

#include <list>
#include "InfoBase.h"

#include "../Skills/Skill.h"

using std::list;

class CharacterInfo : public InfoBase
{
public:
	//TODO:
	// Equipment System
    CharacterInfo(){}
    ~CharacterInfo(){}

	// List of entity's skills
	typedef list<Skill*> SkillList;
	SkillList skills;

	int skill_branch_index[NUM_BRANCHES];

	// Entity EXP
	int EXP = 0;

	inline int CheckLevelUp()
	{
		int levelsGained = 0;
		while (EXP >= stats.GetMaxEXP())
		{
			stats.AddStatPoint(STAT_POINT_GAIN);
			EXP -= stats.GetMaxEXP();
			stats.UpdateStats();
			levelsGained++;
		}
		return levelsGained;
	}
};

#endif