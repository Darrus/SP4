#ifndef SKILLTREESCENE_H
#define SKILLTREESCENE_H

#include "Scene.h"
#include "../FPSCamera.h"
#include "../Skills/SkillFunctions.h"
#include "../Menu/Menu.h"
#include "../Menu/SkillPoint_Display.h"

class SceneManager;
class TextEntity;

class SkillTreeScene : public Scene

{
public:
	SkillTreeScene();
	~SkillTreeScene();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

	void SetCharacter(CharacterInfo* chara);

private:
	FPSCamera camera;
	
	//Character info and how much this character has advanced in each branch
	CharacterInfo* character;

	//Skill trees
	vector<Skill*> skill_branch[NUM_BRANCHES];

	//Menus
	Skill_Menu* skill_menu;
	Menu* utility_menu;

	//GUIObjects 
	SkillDisplay* m_display;
	GUIObject* m_prompt;
	GUIObject* m_current_character_info;
	PopUp_Button* m_popup;
	SkillPoint_Display* display_skill_points;
	CharacterName_Display* display_character_name;

	//Holds the GUIObjects
	vector<GUIObject*>GUIObject_list;

	void dummy_values();
	void init_skills();
	int m_current_party_character;
};

#endif