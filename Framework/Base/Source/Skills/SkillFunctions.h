#ifndef SKILL_CONTAINER_H
#define SKILL_CONTAINER_H

#include "Skill.h"
#include <vector>
#include <map>
#include <SingletonTemplate.h>

using std::vector;
using std::map;

typedef map<string, Skill*> SkillMap;

class SkillContainer : public Singleton<SkillContainer>
{
	friend Singleton<SkillContainer>;
private:
	SkillMap m_skill_container;

public:
	SkillContainer();
	~SkillContainer(); 

	void Init();
	Skill* GetSkill(string name);

};


#endif