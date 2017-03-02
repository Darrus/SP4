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

//============================================================================//
//Brief: A button object adds a CharacterInfo into the Player's Party.		  //
//============================================================================//

class Hire_Button : public Button
{
protected:
	//NOTE TO SELF: I'M GRABBING THE CHARACTER INFO FROM THE CHARACTER PROFILE BUTTON INSTEAD
	//AND THEN CHARACTERPROFILE IS POINTING TO TAVERN_SLOT
	//CharacterInfo* m_chara_to_add;

	int m_gold_cost;

	PopUp_Button* m_popup;
	CharacterProfile_Button* m_target_chara;
public:

	inline void SetGoldCost(int cost)
	{
		m_gold_cost = cost;
		SetTextOffset(40, 15);
		m_text = " Hire Me\nfor" + std::to_string(m_gold_cost) + " gold!";
	}

	inline void SetPopUp(PopUp_Button* popup){ m_popup = popup; }
	inline void SetCharacterToAdd(CharacterProfile_Button* chara_to_add){ m_target_chara = chara_to_add; }
	inline CharacterProfile_Button* GetCharacterToAdd(){ return m_target_chara; }

	inline void RunFunction()
	{
		if (&m_target_chara->m_chara == nullptr)
			return;

		//If player's party is full
		if (Player::GetInstance().GetInstance().GetParty()->memberCount() == Player::GetInstance().GetInstance().GetParty()->GetMaxPartySize())
		{
			m_popup->SetActive(true);
			m_popup->SetText("Your Party is full!");
			return;
		}
		//if player can afford the character
		else if (Player::GetInstance().m_gold < m_gold_cost)
		{
			m_popup->SetActive(true);
			m_popup->SetText("You do not have enough gold!");
			return;
		}
		//If OK, then just add
		else
		{
			if (Player::GetInstance().GetParty()->AddMember(m_target_chara->m_chara))
			{
				m_popup->SetActive(true);
				m_popup->SetText(m_target_chara->m_chara->name + " has joined the Party!");

				m_target_chara->m_chara = nullptr;
				Player::GetInstance().m_gold -= m_gold_cost;
				m_text = "Nobody Here";
			}
		}
	}

	Hire_Button(){ SetScale(650, 150); }
	~Hire_Button(){};
};
