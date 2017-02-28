#include "Skill.h"
#include "..//Character//CharacterInfo.h"
#include <iostream>

class Heal : public Skill
{
private:
	int m_heal_value;

public:
	inline void UseSkill(SkillParameters param)
	{
        int i = 0;
        if (param.caster->MP >= m_mana_cost)
        {
            param.caster->MP -= m_mana_cost;
            for (auto itr = param.targetList.begin(); itr != param.targetList.end(); itr++)
            {
                param.targetList[i]->HP += m_heal_value * param.caster->stats.GetInt();
                ++i;
            }
        }
        else
        {
            std::cout << "Not Enough Mana" << std::endl;
        }
	}

	//TODO:
	//Get these values from Lua/Text file
	Heal() : Skill()
	{
		m_name = "Heal";
		m_heal_value = 25;
		m_mana_cost = 10;
		m_max_target_num = 1;
		m_ally_targetable = true;
		m_enemy_targetable = false;
	};
	~Heal(){};
};

class Sweep : public Skill
{
private:
    int m_dmg_ratio;

public:
    inline void UseSkill(SkillParameters param)
    {
        int i = 0;
        if (param.caster->MP >= m_mana_cost)
        {
            param.caster->MP -= m_mana_cost;
            for (auto itr = param.targetList.begin(); itr != param.targetList.end(); itr++)
            {
                param.targetList[i]->HP -= ((m_dmg_ratio * param.caster->stats.GetDamage()) - param.targetList[i]->stats.GetDefence());
                ++i;
            }
        }
        else
        {
            std::cout << "Not Enough Mana" << std::endl;
        }
    }

    //TODO:
    //Get these values from Lua/Text file
    Sweep() : Skill()
    {
        m_name = "Sweep";
        m_dmg_ratio = 2;
        m_mana_cost = 55;
        m_max_target_num = 1;
        m_ally_targetable = false;
        m_enemy_targetable = true;
    };
    ~Sweep(){};
};

class FireBlast : public Skill
{
private:
    float m_dmg_multi;
public:
    inline void UseSkill(SkillParameters param)
    {
        int i = 0;
        if (param.caster->MP >= m_mana_cost)
        {
            param.caster->MP -= m_mana_cost;
            for (auto itr = param.targetList.begin(); itr != param.targetList.end(); itr++)
            {
                param.targetList[i]->HP -= (m_dmg_multi * (float)param.caster->stats.GetSpellDamage());
                ++i;
            }
        }
        else
        {
            std::cout << "Not Enough Mana" << std::endl;
        }
    }

    //TODO:
    //Get these values from Lua/Text file
    FireBlast() : Skill()
    {
        m_name = "Fire Blast";
        m_dmg_multi = 1.7;
        m_mana_cost = 150;
        m_max_target_num = 1;
        m_ally_targetable = false;
        m_enemy_targetable = true;
    };
    ~FireBlast(){};
};

class HeroMaker : public Skill
{
private:
    int m_heal_value;
    int m_dmg_boost;

public:
    inline void UseSkill(SkillParameters param)
    {
        int i = 0;
        if (param.caster->MP >= m_mana_cost)
        {
            param.caster->MP -= m_mana_cost;
            for (auto itr = param.targetList.begin(); itr != param.targetList.end(); itr++)
            {
                param.targetList[i]->HP += m_heal_value * param.caster->stats.GetInt();
                param.targetList[i]->stats.AddDamage(m_dmg_boost);
                ++i;
            }
        }
        else
        {
            std::cout << "Not Enough Mana" << std::endl;
        }
    }

    //TODO:
    //Get these values from Lua/Text file
    HeroMaker() : Skill()
    {
        m_name = "Hero Maker";
        m_heal_value = 25;
        m_dmg_boost = 500;
        m_mana_cost = 200;
        m_max_target_num = 1;
        m_ally_targetable = true;
        m_enemy_targetable = false;
    };
    ~HeroMaker(){};
};