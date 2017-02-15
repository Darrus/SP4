#ifndef CHARACTER_INFO_H
#define CHARACTER_INFO_H

#define STAT_POINT_GAIN 5

#include <list>
#include "InfoBase.h"

using std::list;

class Skill;

struct CharacterInfo : public InfoBase
{
	//TODO:
	// Equipment System

	// List of entity's skills
	typedef list<Skill*> SkillList;
	SkillList skills;

	// Entity EXP
	int EXP;

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