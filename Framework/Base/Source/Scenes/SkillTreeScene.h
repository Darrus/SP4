#ifndef SKILLTREESCENE_H
#define SKILLTREESCENE_H

#include "Scene.h"
#include "../FPSCamera.h"
#include "../Skills/SkillFunctions.h"
#include "../Menu/Menu.h"

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

	vector<Skill*> skill_branch[NUM_BRANCHES];

	Skill_Menu* skill_menu;

	SkillDisplay* m_display;

	void dummy_values();
	void init_skills();
};

#endif