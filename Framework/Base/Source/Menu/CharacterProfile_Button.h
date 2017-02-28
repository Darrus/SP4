#pragma once
#include "Button.h"

class CharacterProfile_Button : public Button
{
protected:

public:
	CharacterInfo* m_chara;

	inline void SetCharacter(CharacterInfo* chara){ m_chara = chara; }
	inline void ResetAnimation() { m_chara->anim.Reset(); };
	inline void UpdateAnimation() { m_chara->anim.Update(); };
	virtual void Render();
	virtual void RunFunction();

	CharacterProfile_Button();
	virtual ~CharacterProfile_Button();
};

class SelectCharacterForItem_Button : public CharacterProfile_Button
{
protected:
	CharacterInfo* m_target_holder;

public:
	inline void SetCharacterHolder(CharacterInfo *chara){ m_target_holder = chara; }

	virtual void Render();
	virtual void RunFunction(){ /*m_target_holder = m_chara;*/ }

	SelectCharacterForItem_Button(){}
	~SelectCharacterForItem_Button(){}
};