#pragma once
#include "Button.h"

class CharacterProfile_Button : public Button
{
protected:

public:
	CharacterInfo* m_chara;
	bool m_visable_skill_tree;

	inline void SetCharacter(CharacterInfo* chara){ m_chara = chara; }
	inline void SetVisableSkillTree(bool visibilty){ m_visable_skill_tree = visibilty; }
	inline void ResetAnimation() { m_chara->anim.Reset(); }
	inline void UpdateAnimation() { m_chara->anim.Update(); }
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


//============================================================================//
//Brief: A button object kicks a CharacterInfo from the Player's Party.		  //
//============================================================================//
class RemoveMember_Button : public Button
{
protected:

public:
	int m_index_in_party;
	bool m_empty_slot;
	CharacterProfile_Button* chara_btn;
	PopUp_Button* prompt_button;

	inline void RunFunction()
	{
		if (!m_empty_slot)
		{
			if (Player::GetInstance().GetParty()->memberCount() == 1)
			{
				prompt_button->SetActive(true);
				prompt_button->SetText("Cannot remove your last party member!");
				return;
			}
			else
			{
				prompt_button->SetActive(true);
				prompt_button->SetText(chara_btn->m_chara->name + " has left the party!");

				chara_btn->SetCharacter(nullptr);

				delete Player::GetInstance().GetParty()->RemoveMemberByIndex(m_index_in_party);
				m_empty_slot = true;
			}
		}
	}
	inline void Render()
	{
		if (m_empty_slot)
			return;
		else
			Button::Render();
	}

	RemoveMember_Button(){ SetScale(650, 150); }
	~RemoveMember_Button(){};
};