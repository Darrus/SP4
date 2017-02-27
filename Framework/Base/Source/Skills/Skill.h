#ifndef SKILL_H
#define SKILL_H

#include <string>
#include <vector>
#include "Mesh.h"

using std::string;
using std::vector;

class CharacterInfo;

struct SkillParameters
{
	CharacterInfo* caster;
	vector<CharacterInfo*> targetList;
};

enum SKILLTREE_BRANCH
{
	BRANCH_P_ATK,
	BRANCH_M_ATK,
	BRANCH_P_DEF,
	BRANCH_M_DEF,

	NUM_BRANCHES
};

class Skill
{
protected:
	string m_name;
	Mesh* m_icon;
	string m_description;

	int m_max_target_num;
	int m_mana_cost;
	bool m_ally_targetable;
	bool m_enemy_targetable;

public:
	//Getters and Setters
	inline string GetName(){ return m_name; }
	inline void SetName(string setName){ m_name = setName; }

	inline void SetDescription(string desc){ m_description = desc; }
	inline string GetDescription(){	return m_description; }

	inline void SetIcon(Mesh* icon){ m_icon = icon; }
	inline Mesh* GetIcon(){ return m_icon; }

	inline int GetManaCost(){ return m_mana_cost; }

	inline int GetMaxNumberOfTargets(){ return m_max_target_num; }
	inline bool IsAllyTargetable(){ return m_ally_targetable; }
	inline bool IsEnemyTargetable() { return m_enemy_targetable; }

	//Uses the skill 
	virtual void UseSkill(SkillParameters param) = 0;

	Skill() : m_name(""){}
	virtual ~Skill(){}
};



#endif