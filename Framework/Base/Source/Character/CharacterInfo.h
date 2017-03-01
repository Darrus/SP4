#ifndef CHARACTER_INFO_H
#define CHARACTER_INFO_H

#include <list>
#include "InfoBase.h"

#include "../Skills/Skill.h"
#include "../Animation/Animator.h"

using std::list;

class CharacterInfo : public InfoBase
{
public:
	//TODO:
	// Equipment System
    CharacterInfo()
    {
        for (int i = 0; i < NUM_BRANCHES; ++i)
            skill_branch_index[i] = 0;
    }
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
			levelsGained++;
            EXP -= stats.GetMaxEXP();
            stats.AddLevel(1);
            stats.UpdateStats();
            HP = stats.GetMaxHP();
            MP = stats.GetMaxMP();
		}
		return levelsGained;
	}
};

#endif