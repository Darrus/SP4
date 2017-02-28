#pragma once
#include "GUIObject.h"
#include "../Character/CharacterInfo.h"

class CharacterStats_Display : public GUIObject
{
protected:
	CharacterInfo* m_chara;
	
public:
	inline void UpdateAnimation(){ m_chara->anim.Update(); }
	inline void SetTargetCharacter(CharacterInfo* chara){ m_chara = chara; }
	virtual void Render();

	CharacterStats_Display();
	virtual ~CharacterStats_Display();
};