#ifndef BUTTON_H
#define BUTTON_H

#include "GUIObject.h"
#include "SkillDisplay.h"
#include "../Items/Inventory.h"
#include "../../Common/Source/SceneManager.h"
#include "../Skills/SkillFunctions.h"

#include <iostream>
#include <string>

using std::string;

enum BUTTON_MESH
{
	NORMAL_IMAGE = false,
	HIGHLIGHTED_IMAGE,

	NUM_IMAGES
};

//===============================================================//
//Brief: A button object that does something on Press			 //
//===============================================================//
class Button : public GUIObject
{
protected:
	//Holds the image and highlighted image
	Mesh* m_meshList[NUM_IMAGES];

	//boolean to set if the button is clickable

public:
	//To determine which mesh is rendered
	bool m_isPressed;
	bool m_isHovered;
	
	inline void SetButtonImage(Mesh* image) { m_meshList[NORMAL_IMAGE] = image; }
	inline void SetHighlightedImage(Mesh* image) { m_meshList[HIGHLIGHTED_IMAGE] = image; }

	//Virtual function that runs specified button functionality
	inline virtual void RunFunction() = 0;

	//Renders the button
	virtual void Render();

	Button();
	Button(float pos_x, float pos_y, float scale_x, float scale_y);

	inline virtual ~Button(){};
};

//===============================================================//
//Brief: A button object that toggles a boolean		             //
//===============================================================//
class Toggle_Button : public Button
{
protected:
	string m_alt_text;
	//Pointer that points to the address of the boolean to toggle
	bool *m_toToggle;

public:
	//Setters
	inline void SetAlternateText(string alt_text){ m_alt_text = alt_text; }
	inline void SetSwitch(bool &to_toggle){ m_toToggle = &to_toggle; }

	//Virtual function from button class that runs specified button functionality
	inline void RunFunction(){ *m_toToggle = !*m_toToggle; }
	virtual void Render();

	Toggle_Button() : m_toToggle(nullptr){};
	~Toggle_Button(){};
};

//===============================================================//
//Brief: A button object that sets a boolean to a specific value //
//===============================================================//
class SetBool_Button : public Toggle_Button
{
protected:
	//Boolean to set to
	bool m_desired_bool;

public:
	//Always set the boolean to true
	inline void SetBoolean(bool setbool){ m_desired_bool = setbool; }
	inline void RunFunction(){ *m_toToggle = m_desired_bool; }
	void Render();

	SetBool_Button() : Toggle_Button(){};
	~SetBool_Button(){};
};

//===============================================================//
//Brief: A button object that increases an integer				 //
//===============================================================//
class Increment_Button : public Button
{
protected:
	//Pointer that points to the address of the value to increment
	int *m_toIncrease;
	//Amount to increament 
	int m_increment;

public:
	//Setters
	inline void SetTargetValue(int &to_increase){ m_toIncrease = &to_increase; }
	inline void SetIncrementAmount(int value){ m_increment = value; }

	//Virtual function from button class that runs specified button functionality
	inline void RunFunction(){ *m_toIncrease += m_increment; }

	Increment_Button() : m_toIncrease(nullptr), m_increment(1){};
	~Increment_Button(){};
};

//============================================================================//
//Brief: A button object that adds a copy of a set item into target inventory.//
//============================================================================//

class ChangeScene_Button : public Button
{
protected:
	string m_desired_scene;
	bool m_is_overlay_scene;

public:
	//Getters and Setters
	inline void SetDesiredScene(string value){ m_desired_scene = value; }
	inline void SetIsOverlay(bool overlay){ m_is_overlay_scene = overlay; }

	inline void RunFunction(){ SceneManager::GetInstance()->SetActiveScene(m_desired_scene, m_is_overlay_scene); }

	ChangeScene_Button() : m_is_overlay_scene(false){}
	~ChangeScene_Button(){}
};

//============================================================================//
//Brief: A button object that goes back to the previous scene.				  //
//============================================================================//

class PreviousScene_Button : public Button
{
protected:

public:
	inline void RunFunction(){ SceneManager::GetInstance()->PreviousScene(); }

	PreviousScene_Button(){}
	~PreviousScene_Button(){}
};

//===============================================================================//
//Brief: A button object that changes the value of the target to a desired value.//
//===============================================================================//

class ChangeValue_Button : public Button
{
protected:
	//Pointer that points to the address of the value to increment
	int *m_set_value;
	//Amount to increament 
	int m_target_value;

public:
	//Getters and Setters
	inline void SetTargetValue(int &set_value){ m_set_value = &set_value; }

	inline void RunFunction(){ *m_set_value = m_target_value; }

	ChangeValue_Button(){}
	~ChangeValue_Button(){}
};

//===============================================================================//
//Brief: A button object that acts as a prompt that disappears after click.		 //
//===============================================================================//
class PopUp_Button : public Button
{
protected:

public:
	//Getters and Setters
	inline void RunFunction(){ m_isActive = false; }
	inline void Render()
	{ 
		if (!m_isActive)
			return;
		MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
		modelStack.PushMatrix();
		modelStack.Translate(m_pos_x, m_pos_y, 8);

		modelStack.PushMatrix();
		modelStack.Scale(m_scale_x, m_scale_y, 1);
		if (m_meshList[m_isHovered] != nullptr)
			RenderHelper::RenderMesh(m_meshList[m_isHovered]);
		modelStack.PopMatrix();

		if (m_text != "")
		{
			//Offset for text
			modelStack.Translate(-m_scale_x * 0.5, 0, 1);
			modelStack.Translate(m_text_offset_x, m_text_offset_y, 0);
			modelStack.Scale(m_text_scale_x, m_text_scale_y, 1);
			RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), m_text, Color(1, 0, 0));	//NOTE: COLOUR DOESN'T WORK. THANKS ALOT, TOH.
		}

		modelStack.PopMatrix();
	}

	PopUp_Button(){}
	~PopUp_Button(){}
};

//============================================================================//
//Brief: A button object that adds a copy of a set item into target inventory.//
//============================================================================//
class ShopItem_Button : public Button
{
protected:
	Item *m_item;
	Inventory *m_targetInventory;

public:
	inline void SetTargetInventory(Inventory &target_inven){ m_targetInventory = &target_inven; }
	inline void SetItem(Item &target_item){ m_item = &target_item; }
	inline void RunFunction()
	{ 
		Item* itemToAdd = new Item();
		*itemToAdd = *m_item;
		m_targetInventory->AddCopy(itemToAdd);
	}
	virtual void Render();

	ShopItem_Button()
	{
		//Scale ratio of about 3:1 is ideal
		SetScale(650, 150);
	};
	~ShopItem_Button(){};
};

//============================================================================//
//Brief: A button object that hold the index of an Item object and			  //
//		 then disappears when pressed.										  //
//============================================================================//
class ShopCart_Button : public Button
{
protected:
	Inventory *m_targetInventory;
	int m_item_index;

public: 
	inline void SetIndex(int item_index){ m_item_index = item_index; }
	inline void SetTargetInventory(Inventory &target_inven){ m_targetInventory = &target_inven; }

	inline void RunFunction()
	{
		m_targetInventory->m_inventoryList.erase(m_targetInventory->m_inventoryList.begin() + m_item_index);
		m_isActive = false;
	}

	virtual void Render();

	ShopCart_Button() : Button(){};
	~ShopCart_Button(){};
};

//==============================================================================//
//Brief: A button object that hold the index of an Item object which sends the  // 
//		 item into another inventory and then disappears when pressed.          //
//==============================================================================//
class TransferToInventory_Button : public ShopCart_Button
{
protected:
	Inventory *m_receiving_inventory;

public:
	inline void SetReceivingInventory(Inventory &recv_inven){ m_receiving_inventory = &recv_inven; }

	inline void RunFunction()
	{
		m_receiving_inventory->AddCopy(m_targetInventory->m_inventoryList[m_item_index]);
		ShopCart_Button::RunFunction();
	}

	TransferToInventory_Button() : ShopCart_Button(){};
	~TransferToInventory_Button(){};
};


//==============================================================================//
//Brief: A button object that has the ability to pass the character a skill		//
//		 pointer into the character's info skill list.							//
//==============================================================================//

class Skill_Button : public Button
{
protected:
	Skill* m_skill;
	SkillDisplay* m_target_display;
	CharacterInfo* m_target_character;
	bool m_is_skill_learnt;
	int m_branch;
	int m_index_in_branch;

public:
	inline void SetSkill(Skill* skill){ m_skill = skill; }
	inline void SetIsSkillLearnt(bool skil_is_learnt){ m_is_skill_learnt = skil_is_learnt; }
	inline void SetTargetDisplay(SkillDisplay* display){ m_target_display = display; }
	inline void SetBranch(int branch){ m_branch = branch; }
	inline void SetIndexInBranch(int index_in_branch){ m_index_in_branch = index_in_branch; }
	inline void SetTargetCharacter(CharacterInfo* target_character){ m_target_character = target_character; }

	inline void LearnSkill()
	{
		if (!m_is_skill_learnt)
		{
			if (m_target_character->skill_branch_index[m_branch] == m_index_in_branch)
			{
				m_target_character->skill_branch_index[m_branch]++;
				m_is_skill_learnt = true;
				m_target_character->skills.push_back(SkillContainer::GetInstance()->GetSkill(m_skill->GetName()));
			}
		}
	}

	inline void RunFunction()
	{
		m_target_display->SetSkillToDisplay(m_skill);
	}
	void Render();

	Skill_Button(){};
	~Skill_Button(){};

};

//class Skill_Button : public Button
//{
//protected:
//	Skill* m_skill;
//	CharacterInfo* m_target_character;
//
//public:
//	inline void SetTargetCharacter(CharacterInfo &target_character){ m_target_character = &target_character; }
//	inline void SetSkill(Skill* skill){ m_skill = skill; }
//	inline void RunFunction()
//	{
//		if (!m_is_skill_learnt)
//		{
//			if (m_target_character->skill_branch_index[m_branch] == m_index_in_branch)
//			{
//				m_target_character->skill_branch_index[m_branch]++;
//				m_is_skill_learnt = true;
//				m_target_character->skills.push_back(SkillContainer::GetInstance()->GetSkill(m_skill_name));
//			}
//		}
//	}
//	void Render();
//
//	Skill_Button(){};
//	~Skill_Button(){};
//
//};

#endif