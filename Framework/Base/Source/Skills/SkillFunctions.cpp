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
    Curate* curate = new Curate();
    m_skill_container.insert(std::make_pair(curate->GetName(), curate));
    HeroMaker* hero = new HeroMaker();
    m_skill_container.insert(std::make_pair(hero->GetName(), hero));
    Charisma* charisma = new Charisma();
    m_skill_container.insert(std::make_pair(charisma->GetName(), charisma));
    Illusion* illusion = new Illusion();
    m_skill_container.insert(std::make_pair(illusion->GetName(), illusion));


    Thrust* thrust = new Thrust();
    m_skill_container.insert(std::make_pair(thrust->GetName(), thrust));
    Sweep* sweep = new Sweep();
    m_skill_container.insert(std::make_pair(sweep->GetName(), sweep));
    Feint* feint = new Feint();
    m_skill_container.insert(std::make_pair(feint->GetName(), feint));
    SpeedBoost* speedboost = new SpeedBoost();
    m_skill_container.insert(std::make_pair(speedboost->GetName(), speedboost));
    PowerThrust* powerthrust = new PowerThrust();
    m_skill_container.insert(std::make_pair(powerthrust->GetName(), powerthrust));


    FireBlast* blast = new FireBlast();
    m_skill_container.insert(std::make_pair(blast->GetName(), blast));
    Firaga* firaga = new Firaga();
    m_skill_container.insert(std::make_pair(firaga->GetName(), firaga));
    IceBlast* iceblast = new IceBlast();
    m_skill_container.insert(std::make_pair(iceblast->GetName(), iceblast));
    Blizzaga* blizzaga = new Blizzaga();
    m_skill_container.insert(std::make_pair(blizzaga->GetName(), blizzaga));
    BliFirga* blifirga = new BliFirga();
    m_skill_container.insert(std::make_pair(blifirga->GetName(), blifirga));
}

Skill* SkillContainer::GetSkill(string name)
{
	SkillMap::iterator it = m_skill_container.find(name);
	if (it != m_skill_container.end())
		return (it)->second;
	else
		return nullptr;
}