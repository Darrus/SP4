#ifndef SKILL_H
#define SKILL_H

#include <string>
#include <vector>

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
public:

protected:
	string m_name;

	int m_max_target_num;
	int m_mana_cost;
	bool m_ally_targetable;
	bool m_enemy_targetable;
public:
	//Getters and Setters
	inline string GetName(){ return m_name; }
	inline void SetName(string setName){ m_name = setName; }

	//Getters and Setters
	inline int GetMaxNumberOfTargets(){ return m_max_target_num; }
	inline bool IsAllyTargetable(){ return m_ally_targetable; }
	inline bool IsEnemyTargetable() { return m_enemy_targetable; }

	//Uses the skill 
	virtual void UseSkill(SkillParameters param) = 0;

	Skill() : m_name(""){}
	virtual ~Skill(){}
};



#endif