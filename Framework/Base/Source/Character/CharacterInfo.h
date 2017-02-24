#ifndef CHARACTER_INFO_H
#define CHARACTER_INFO_H

#define STAT_POINT_GAIN 5

#include <list>
#include "InfoBase.h"

using std::list;

class Skill;

class CharacterInfo : public InfoBase
{
public:
	//TODO:
	// Equipment System
    CharacterInfo(){}
    virtual ~CharacterInfo(){}

	// List of entity's skills
	typedef list<Skill*> SkillList;
	SkillList skills;

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
            HP = stats.GetMaxHP();
            MP = stats.GetMaxMP();
			levelsGained++;
		}
		return levelsGained;
	}
};

#endif