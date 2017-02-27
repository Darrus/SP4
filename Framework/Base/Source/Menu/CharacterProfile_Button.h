#pragma once
#include "Button.h"
#include "../Scenes/SkillTreeScene.h"
#include "../Menu/SkillDisplay.h"

class CharacterProfile_Button :
	public Button
{
protected:
	CharacterInfo* m_chara;

public:
	inline void SetCharacter(CharacterInfo* chara){ m_chara = chara; }
	virtual void Render();
	virtual void RunFunction()
	{
		dynamic_cast<SkillTreeScene*>(SceneManager::GetInstance()->SetActiveScene("SkillTreeScene", true))->SetCharacter(m_chara);
	}

	CharacterProfile_Button();
	virtual ~CharacterProfile_Button();
};

