#ifndef SKILL_H
#define SKILL_H

#include <string>
#include <functional>

#include "SkillFunctions.h"
#include "../Character/CharacterInfo.h"

using std::string;
using std::function;

//#define SKILL_VER 2;

//#if SKILL_VER == 1
//
//class Skill
//{
//protected:
//	string m_name;
//	function<void (SkillParameters*)> m_funcptr;
//
//	int m_max_target_num;
//
//	bool m_self_targetable;
//	bool m_ally_targetable;
//	bool m_enemy_targetable;
//
//public:
//
//	//Getters and Setters
//	inline int GetMaxNumberTargets(){ return m_max_target_num; }
//	inline bool IsSelfTargetable(){ return m_self_targetable; }
//	inline bool IsAllyTargetable(){ return m_ally_targetable; }
//	inline bool IsEnemyTargetable() { return m_enemy_targetable; }
//	inline string GetName(){ return m_name; }
//
//	inline void SetName(string setName){ m_name = setName; }
//	inline void SetSkill(function<void(SkillParameters*)> func){ m_funcptr = func; }
//
//	//Uses the skill 
//	inline virtual void UseSkill(SkillParameters* param){ m_funcptr(param); }
//
//	Skill() :
//		m_name(""),
//		m_self_targetable(false),
//		m_ally_targetable(false),
//		m_enemy_targetable(false),
//		m_max_target_num(-1),
//		m_funcptr(nullptr){}
//
//	virtual ~Skill(){};
//};
//
//#endif

class Skill
{
protected:
	CharacterInfo* m_caster;
	string m_name;

public:
	//Getters and Setters
	inline string GetName(){ return m_name; }
	inline void SetName(string setName){ m_name = setName; }
	inline void SetCaster(CharacterInfo* caster){ m_caster = caster; }

	//Uses the skill 
	inline virtual void UseSkill() = 0;

	Skill() : m_name(""){}

	virtual ~Skill(){}
};

class Skill_GroupCast
{
protected:
	int m_max_target_num;
	bool m_ally_targetable;
	bool m_enemy_targetable;

	std::vector<CharacterInfo*> m_targetList;

public:
	//Getters and Setters
	inline bool IsAllyTargetable(){ return m_ally_targetable; }
	inline bool IsEnemyTargetable() { return m_enemy_targetable; }

	inline bool AddTarget(CharacterInfo* target){ m_targetList.push_back(target); }

	inline int GetNumberOfTargets(){ return m_max_target_num; }

	Skill_GroupCast();
	virtual ~Skill_GroupCast();
};

class Skill_SingleTarget
{
protected:
	CharacterInfo* m_targetList;

public:
	//Getters and Setters
	inline void SetTarget(CharacterInfo* target){ m_targetList = target; }

	Skill_SingleTarget();
	virtual ~Skill_SingleTarget();
};

#endif