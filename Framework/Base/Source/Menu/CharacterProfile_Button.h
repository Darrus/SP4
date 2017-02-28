#pragma once
#include "Button.h"
//#include "../Scenes/SkillTreeScene.h"

class CharacterProfile_Button :
	public Button
{
protected:
	CharacterInfo* m_chara;

public:
	inline void SetCharacter(CharacterInfo* chara){ m_chara = chara; }
	inline void ResetAnimation() { m_chara->anim.Reset(); };
	inline void UpdateAnimation() { m_chara->anim.Update(); };
	virtual void Render();
	//TODO:
	//This button is supposed to bring them to the character profile/info page, NOT directly to the skill tree scene
	virtual void RunFunction()
	{
		//dynamic_cast<SkillTreeScene*>(SceneManager::GetInstance()->SetActiveScene("SkillTreeScene", true))->SetCharacter(m_chara);
		SceneManager::GetInstance()->SetActiveScene("SkillTreeScene", true);
	}
	CharacterProfile_Button();
	virtual ~CharacterProfile_Button();
};

