#ifndef CHARACTER_INFO_H
#define CHARACTER_INFO_H

#define STAT_POINT_GAIN 5

#include <list>
#include "InfoBase.h"

#include "../Skills/Skill.h"
#include "../Animation/Animator.h"

using std::list;

class CharacterInfo : public InfoBase
{
public:
	// Equipment System
    CharacterInfo(){}
    virtual ~CharacterInfo(){}

	// Animator
	Animator anim;

	// List of entity's skills
	typedef list<Skill*> SkillList;
	SkillList skills;

	int skill_branch_index[NUM_BRANCHES];

	virtual void Update()
	{
		anim.Update();
	}

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