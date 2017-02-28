#pragma once
#include "GUIObject.h"
#include "../Character/CharacterInfo.h"

class SkillPoint_Display : public GUIObject
{
protected:
	CharacterInfo* m_target_character;
	
public:
	inline void SetTargetCharacter(CharacterInfo* chara){ m_target_character = chara; }
	virtual void Render();

	SkillPoint_Display();
	virtual ~SkillPoint_Display();
};

class CharacterName_Display : public SkillPoint_Display
{
protected:

public:
	virtual void Render();

	CharacterName_Display(){}
	~CharacterName_Display(){}
};