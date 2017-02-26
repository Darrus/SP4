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