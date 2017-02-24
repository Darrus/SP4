#include "Skill.h"
#include "..//Character//CharacterInfo.h"

class Heal : public Skill
{
private:
	int m_heal_value;

public:
	inline void UseSkill(SkillParameters param)
	{
		param.caster->MP -= m_mana_cost;
		param.targetList[0]->HP += m_heal_value * param.caster->stats.GetInt();
	}

	//TODO:
	//Get these values from Lua/Text file
	Heal() : Skill()
	{
		m_name = "Heal";
		m_heal_value = 1000;
		m_mana_cost = 10;
		m_max_target_num = 1;
		m_ally_targetable = true;
		m_enemy_targetable = false;
	};
	~Heal(){};
};