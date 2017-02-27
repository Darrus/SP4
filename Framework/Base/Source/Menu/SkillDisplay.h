#pragma once
#include "GUIObject.h"
#include "../Skills/Skill.h"

class SkillDisplay :
	public GUIObject
{
protected:
	Skill* m_skill;

public:
	inline void SetSkillToDisplay(Skill* skill){ m_skill = skill; }
	virtual void Render();

	SkillDisplay();
	virtual ~SkillDisplay();
};

