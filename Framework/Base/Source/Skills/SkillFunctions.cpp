#include "SkillFunctions.h"
#include "Skill.cpp"

SkillContainer::SkillContainer()
{
	
}

SkillContainer::~SkillContainer()
{
	SkillMap::iterator it = m_skill_container.begin();
	while (it != m_skill_container.end())
		it = m_skill_container.erase(it);
}

void SkillContainer::Init()
{
	Heal* heal = new Heal();
	m_skill_container.insert(std::make_pair(heal->GetName(), heal));
    Sweep* sweep = new Sweep();
    m_skill_container.insert(std::make_pair(sweep->GetName(), sweep));
    FireBlast* blast = new FireBlast();
    m_skill_container.insert(std::make_pair(blast->GetName(), blast));
    HeroMaker* hero = new HeroMaker();
    m_skill_container.insert(std::make_pair(hero->GetName(), hero));
}

Skill* SkillContainer::GetSkill(string name)
{
	SkillMap::iterator it = m_skill_container.find(name);
	if (it != m_skill_container.end())
		return (it)->second;
	else
		return nullptr;
}