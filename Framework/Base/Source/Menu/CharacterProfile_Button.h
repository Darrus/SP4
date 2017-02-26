#pragma once
#include "Button.h"
class CharacterProfile_Button :
	public Button
{
protected:
	CharacterInfo* m_chara;

public:
	inline void SetCharacter(CharacterInfo* chara){ m_chara = chara; }
	virtual void Render();

	CharacterProfile_Button();
	virtual ~CharacterProfile_Button();
};

