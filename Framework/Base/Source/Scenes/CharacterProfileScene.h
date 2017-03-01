#pragma once
#include <vector>
#include <string>

#include "Scene.h"
#include "../Menu/Menu.h"
#include "../Menu/CharacterProfile_Button.h"
#include "../Menu/CharacterStatsDisplay.h"

using std::vector;
using std::string;

class CharacterProfileScene : public Scene
{
protected:
	//GUIObjects
	GUIObject* m_header_text;
	CharacterStats_Display* m_chara_stats;
	
	//Button to go to Skill Tree Scene
	ChangeScene_Button* goto_skill_tree_scene_btn;

	//Menus
	Menu* utility_menu;

	//Dummy character
	CharacterInfo* current_character;

public:
	CharacterProfileScene();
	virtual ~CharacterProfileScene();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

	inline void SetCharacter(CharacterInfo* chara, bool show_skilltree)
	{
		current_character = chara;
		m_chara_stats->SetTargetCharacter(current_character);

		//Only activates the button for skill tree when it is a from a character currently in the party
		//Beacuse sometimes the scene is accessed from Tavern
		goto_skill_tree_scene_btn->SetActive(show_skilltree);
	}
};

