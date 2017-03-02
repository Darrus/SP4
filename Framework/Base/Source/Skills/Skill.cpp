#include "Skill.h"
#include "..//Character//CharacterInfo.h"
#include <iostream>

///< Healer Skills
///< Heals an Ally
class Heal : public Skill
{
private:
    int m_heal_value;

public:
    inline bool UseSkill(SkillParameters param)
    {
        if (param.caster->MP >= m_mana_cost)
        {
            param.caster->MP -= m_mana_cost;
            param.targetList[0]->HP += m_heal_value * param.caster->stats.GetInt();
            if (param.targetList[0]->HP > param.targetList[0]->stats.GetMaxHP())
                param.targetList[0]->HP = param.targetList[0]->stats.GetMaxHP();

            return true;
        }
        else
            return false;
    }

    //TODO:
    //Get these values from Lua/Text file
    Heal() : Skill()
    {
        m_name = "Heal";
        m_heal_value = 75;
        m_mana_cost = 60;
        m_max_target_num = 1;
        m_ally_targetable = true;
        m_enemy_targetable = false;
    };
    ~Heal(){};
};

///< Heals all Ally
class Curate : public Skill
{
private:
    int m_heal_value;

public:
    inline bool UseSkill(SkillParameters param)
    {
        int i = 0;
        if (param.caster->MP >= m_mana_cost)
        {
            param.caster->MP -= m_mana_cost;
            for (auto itr = param.targetList.begin(); itr != param.targetList.end(); itr++)
            {
                param.targetList[i]->HP += m_heal_value * param.caster->stats.GetInt();
                if (param.targetList[i]->HP > param.targetList[i]->stats.GetMaxHP())
                    param.targetList[i]->HP = param.targetList[i]->stats.GetMaxHP();
                ++i;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    //TODO:
    //Get these values from Lua/Text file
    Curate() : Skill()
    {
        m_name = "Curate";
        m_heal_value = 25;
        m_mana_cost = 80;
        m_max_target_num = 4;
        m_ally_targetable = true;
        m_enemy_targetable = false;
    };
    ~Curate(){};
};

///< Increase Overall Damage and Heal an ally
class HeroMaker : public Skill
{
private:
    int m_heal_value;
    int m_dmg_boost;

public:
    inline bool UseSkill(SkillParameters param)
    {
        if (param.caster->MP >= m_mana_cost)
        {
            param.caster->MP -= m_mana_cost;
            param.targetList[0]->HP += m_heal_value * param.caster->stats.GetInt();
            param.targetList[0]->stats.AddDamage(m_dmg_boost);

            if (param.targetList[0]->HP > param.targetList[0]->stats.GetMaxHP())
                param.targetList[0]->HP = param.targetList[0]->stats.GetMaxHP();
            return true;
        }
        else
        {
            return false;
        }
    }

    //TODO:
    //Get these values from Lua/Text file
    HeroMaker() : Skill()
    {
        m_name = "Hero Maker";
        m_heal_value = 50;
        m_dmg_boost = 250;
        m_mana_cost = 200;
        m_max_target_num = 1;
        m_ally_targetable = true;
        m_enemy_targetable = false;
    };
    ~HeroMaker(){};
};

///< Increases overall damage for that battle.
class Charisma : public Skill
{
private:
    double m_dmg_boost;

public:
    inline bool UseSkill(SkillParameters param)
    {
        int i = 0;
        if (param.caster->MP >= m_mana_cost)
        {
            param.caster->MP -= m_mana_cost;
            for (auto itr = param.targetList.begin(); itr != param.targetList.end(); itr++)
            {
                param.targetList[i]->stats.AddDamage(m_dmg_boost);
                ++i;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    //TODO:
    //Get these values from Lua/Text file
    Charisma() : Skill()
    {
        m_name = "Charisma";
        m_dmg_boost = 400;
        m_mana_cost = 170;
        m_max_target_num = 4;
        m_ally_targetable = true;
        m_enemy_targetable = false;
    };
    ~Charisma(){};
};

///< Reduces Enemy DEX (Crit and Dodge for a turn)
class Illusion : public Skill
{
private:
    double m_drop_rate;

public:
    inline bool UseSkill(SkillParameters param)
    {
        int i = 0;
        if (param.caster->MP >= m_mana_cost)
        {
            param.caster->MP -= m_mana_cost;
            for (auto itr = param.targetList.begin(); itr != param.targetList.end(); itr++)
            {
                param.targetList[i]->stats.AddDodgeRate(param.targetList[i]->stats.GetDex() - (m_drop_rate * param.caster->stats.GetInt()));
                ++i;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    //TODO:
    //Get these values from Lua/Text file
    Illusion() : Skill()
    {
        m_name = "Illusion";
        m_drop_rate = 0.2;
        m_mana_cost = 150;
        m_max_target_num = 4;
        m_ally_targetable = false;
        m_enemy_targetable = true;
    };
    ~Illusion(){};
};
///< End of Healer Skills

///< Attacker Skills
///< Attacks all enemies with a sweep
class Thrust : public Skill
{
private:
    double m_dmg_ratio;

public:
    inline bool UseSkill(SkillParameters param)
    {
        if (param.caster->MP >= m_mana_cost)
        {
            param.caster->MP -= m_mana_cost;
            param.targetList[0]->HP -= ((m_dmg_ratio * param.caster->stats.GetDamage()) - param.targetList[0]->stats.GetDefence());
            if (param.targetList[0]->HP <= 0)
                param.targetList[0]->HP = 0;

            return true;
        }
        else
        {
            return false;
        }
    }

    //TODO:
    //Get these values from Lua/Text file
    Thrust() : Skill()
    {
        m_name = "Thrust";
        m_dmg_ratio = 1.8;
        m_mana_cost = 30;
        m_max_target_num = 1;
        m_ally_targetable = false;
        m_enemy_targetable = true;
    };
    ~Thrust(){};
};

///< Attacks all enemies with a sweep
class Sweep : public Skill
{
private:
    double m_dmg_ratio;

public:
    inline bool UseSkill(SkillParameters param)
    {
        int i = 0;
        if (param.caster->MP >= m_mana_cost)
        {
            param.caster->MP -= m_mana_cost;
            for (auto itr = param.targetList.begin(); itr != param.targetList.end(); itr++)
            {
                param.targetList[i]->HP -= ((m_dmg_ratio * param.caster->stats.GetDamage()) - param.targetList[i]->stats.GetDefence());
                if (param.targetList[i]->HP <= 0)
                    param.targetList[i]->HP = 0;
                ++i;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    //TODO:
    //Get these values from Lua/Text file
    Sweep() : Skill()
    {
        m_name = "Sweep";
        m_dmg_ratio = 0.8;
        m_mana_cost = 55;
        m_max_target_num = 4;
        m_ally_targetable = false;
        m_enemy_targetable = true;
    };
    ~Sweep(){};
};

///< Attacks an Enemy with a Feint strike, slows enemy recharge rate.
class Feint : public Skill
{
private:
    double m_dmg_ratio;
    double m_slow_ratio;

public:
    inline bool UseSkill(SkillParameters param)
    {
        if (param.caster->MP >= m_mana_cost)
        {
            param.caster->MP -= m_mana_cost;
            param.targetList[0]->HP -= (m_dmg_ratio * (float)param.caster->stats.GetDamage());

            param.targetList[0]->stats.DeductRechargeRate(param.targetList[0]->stats.GetAgi() - (m_slow_ratio * param.caster->stats.GetAgi()));

            if (param.targetList[0]->HP <= 0)
                param.targetList[0]->HP = 0;

            if (param.targetList[0]->stats.GetRechargeRate() < 0)
                param.targetList[0]->stats.AddRechargeRate(1);

            return true;
        }
        else
        {
            return false;
        }
    }

    //TODO:
    //Get these values from Lua/Text file
    Feint() : Skill()
    {
        m_name = "Feint";
        m_dmg_ratio = 1.2;
        m_slow_ratio = 0.15;
        m_mana_cost = 80;
        m_max_target_num = 1;
        m_ally_targetable = false;
        m_enemy_targetable = true;
    };
    ~Feint(){};
};

///< Provides the whole team fast AGI till their turn starts
class SpeedBoost : public Skill
{
private:
    double m_boost_rate;

public:
    inline bool UseSkill(SkillParameters param)
    {
        int i = 0;
        if (param.caster->MP >= m_mana_cost)
        {
            param.caster->MP -= m_mana_cost;
            for (auto itr = param.targetList.begin(); itr != param.targetList.end(); itr++)
            {
                param.targetList[i]->stats.AddRechargeRate(param.targetList[i]->stats.GetAgi() - (m_boost_rate * param.caster->stats.GetInt()));
                ++i;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    SpeedBoost() : Skill()
    {
        m_name = "Speed Boost";
        m_boost_rate = 0.15;
        m_mana_cost = 150;
        m_max_target_num = 4;
        m_ally_targetable = true;
        m_enemy_targetable = false;
    };
    ~SpeedBoost(){};
};

///< Attacks an Enemy with a powerful strike
class PowerThrust : public Skill
{
private:
    float m_dmg_ratio;

public:
    inline bool UseSkill(SkillParameters param)
    {
        int i = 0;
        if (param.caster->MP >= m_mana_cost)
        {
            param.caster->MP -= m_mana_cost;
            param.targetList[0]->HP -= ((m_dmg_ratio * param.caster->stats.GetDamage()) - param.targetList[0]->stats.GetDefence());
            if (param.targetList[0]->HP <= 0)
                param.targetList[0]->HP = 0;

            return true;
        }
        else
        {
            return false;
        }
    }

    //TODO:
    //Get these values from Lua/Text file
    PowerThrust() : Skill()
    {
        m_name = "Power Thrust";
        m_dmg_ratio = 2.5;
        m_mana_cost = 80;
        m_max_target_num = 1;
        m_ally_targetable = false;
        m_enemy_targetable = true;
    };
    ~PowerThrust(){};
};
///< End of Attacker Skills

///< Spell damage Skills
///< Blasts an enemy with intense heat
class FireBlast : public Skill
{
private:
    float m_dmg_multi;
public:
    inline bool UseSkill(SkillParameters param)
    {
        if (param.caster->MP >= m_mana_cost)
        {
            param.caster->MP -= m_mana_cost;
            param.targetList[0]->HP -= (m_dmg_multi * (float)param.caster->stats.GetSpellDamage());
            if (param.targetList[0]->HP <= 0)
                param.targetList[0]->HP = 0;
            return true;
        }
        else
        {
            return false;
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

///< Attacks all enemy with intense heat
class Firaga : public Skill
{
private:
    float m_dmg_multi;
public:
    inline bool UseSkill(SkillParameters param)
    {
        int i = 0;
        if (param.caster->MP >= m_mana_cost)
        {
            param.caster->MP -= m_mana_cost;
            for (auto itr = param.targetList.begin(); itr != param.targetList.end(); itr++)
            {
                param.targetList[i]->HP -= (m_dmg_multi * (float)param.caster->stats.GetSpellDamage());

                if (param.targetList[i]->HP <= 0)
                    param.targetList[i]->HP = 0;
                ++i;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    //TODO:
    //Get these values from Lua/Text file
    Firaga() : Skill()
    {
        m_name = "Firaga";
        m_dmg_multi = 1.1;
        m_mana_cost = 200;
        m_max_target_num = 4;
        m_ally_targetable = false;
        m_enemy_targetable = true;
    };
    ~Firaga(){};
};

///< Blasts an enemy with intense chill and slows enemy for a turn
class IceBlast : public Skill
{
private:
    double m_dmg_multi;
    double m_drop_rate;
public:
    inline bool UseSkill(SkillParameters param)
    {
        if (param.caster->MP >= m_mana_cost)
        {
            param.caster->MP -= m_mana_cost;
            param.targetList[0]->HP -= (m_dmg_multi * (float)param.caster->stats.GetSpellDamage());

            param.targetList[0]->stats.DeductRechargeRate(param.targetList[0]->stats.GetRechargeRate() - (m_drop_rate * param.caster->stats.GetInt()));

            if (param.targetList[0]->stats.GetRechargeRate() < 0)
                param.targetList[0]->stats.AddRechargeRate(1);

            if (param.targetList[0]->HP <= 0)
                param.targetList[0]->HP = 0;
            return true;
        }
        else
        {
            return false;
        }
    }

    //TODO:
    //Get these values from Lua/Text file
    IceBlast() : Skill()
    {
        m_name = "Ice Blast";
        m_dmg_multi = 1.2;
        m_drop_rate = 0.2;
        m_mana_cost = 180;
        m_max_target_num = 1;
        m_ally_targetable = false;
        m_enemy_targetable = true;
    };
    ~IceBlast(){};
};

///< Blasts an enemy with intense chill and slows enemy for a turn
class Blizzaga : public Skill
{
private:
    int m_dmg_multi;
    double m_drop_rate;
public:
    inline bool UseSkill(SkillParameters param)
    {
        int i = 0;
        if (param.caster->MP >= m_mana_cost)
        {
            param.caster->MP -= m_mana_cost;
            for (auto itr = param.targetList.begin(); itr != param.targetList.end(); itr++)
            {
                param.targetList[i]->HP -= (m_dmg_multi * (float)param.caster->stats.GetSpellDamage());

                int deductrate = param.targetList[i]->stats.GetRechargeRate() - (m_drop_rate * param.caster->stats.GetInt());

                //if (param.targetList[i]->stats.GetRechargeRate() - deductrate <= 0)
                //    deductrate = 0;
                param.targetList[i]->stats.DeductRechargeRate(param.targetList[i]->stats.GetRechargeRate() - (m_drop_rate * param.caster->stats.GetInt()));

                if (param.targetList[i]->stats.GetRechargeRate() < 0)
                    param.targetList[i]->stats.AddRechargeRate(1);

                if (param.targetList[i]->HP <= 0)
                    param.targetList[i]->HP = 0;
                ++i;
            }

            return true;
        }
        else
        {
            return false;
        }
    }

    //TODO:
    //Get these values from Lua/Text file
    Blizzaga() : Skill()
    {
        m_name = "Blizzaga";
        m_dmg_multi = 1;
        m_drop_rate = 0.15;
        m_mana_cost = 250;
        m_max_target_num = 4;
        m_ally_targetable = false;
        m_enemy_targetable = true;
    };
    ~Blizzaga(){};
};

///< Blasts all enemies with both intense freeze and fire. slows for a turn
class BliFirga : public Skill
{
private:
    int m_dmg_multi;
    double m_drop_rate;
public:
    inline bool UseSkill(SkillParameters param)
    {
        int i = 0;
        if (param.caster->MP >= m_mana_cost)
        {
            param.caster->MP -= m_mana_cost;
            for (auto itr = param.targetList.begin(); itr != param.targetList.end(); itr++)
            {
                param.targetList[i]->HP -= (m_dmg_multi * (float)param.caster->stats.GetSpellDamage());

                param.targetList[i]->stats.DeductRechargeRate(param.targetList[i]->stats.GetRechargeRate() - (m_drop_rate * param.caster->stats.GetInt()));

                if (param.targetList[i]->stats.GetRechargeRate() < 0)
                    param.targetList[i]->stats.AddRechargeRate(1);

                if (param.targetList[i]->HP <= 0)
                    param.targetList[i]->HP = 0;

                param.targetList[i]->stats.UpdateStats();

                ++i;
            }

            return true;
        }
        else
        {
            return false;
        }
    }

    //TODO:
    //Get these values from Lua/Text file
    BliFirga() : Skill()
    {
        m_name = "BliFirga";
        m_dmg_multi = 2;
        m_drop_rate = 0.2;
        m_mana_cost = 325;
        m_max_target_num = 4;
        m_ally_targetable = false;
        m_enemy_targetable = true;
    };
    ~BliFirga(){};
};
///> End of Spell dmg Skills

/////< Random Skills
/////< Reduces Enemy Damage for a turn
//class ATBBoost : public Skill
//{
//private:
//    int m_atb_pt;
//public:
//    inline bool UseSkill(SkillParameters param)
//    {
//        if (param.caster->MP >= m_mana_cost)
//        {
//            param.caster->MP -= m_mana_cost;
//            //param.targetList[0]->stats.ded -= (m_atb_pt * (float)param.caster->stats.GetSpellDamage());
//        }
//        else
//        {
//            return false;
//        }
//    }
//
//    //TODO:
//    //Get these values from Lua/Text file
//    ATBBoost() : Skill()
//    {
//        m_name = "ATBBoost";
//        m_atb_pt = 2;
//        m_mana_cost = 200;
//        m_max_target_num = 1;
//        m_ally_targetable = false;
//        m_enemy_targetable = true;
//    };
//    ~ATBBoost(){};
//};
//
//class Sabotage : public Skill
//{
//private:
//    float m_dmg_multi;
//public:
//    inline bool UseSkill(SkillParameters param)
//    {
//        int i = 0;
//        if (param.caster->MP >= m_mana_cost)
//        {
//            param.caster->MP -= m_mana_cost;
//            for (auto itr = param.targetList.begin(); itr != param.targetList.end(); itr++)
//            {
//                param.targetList[i]->HP -= (m_dmg_multi * (float)param.caster->stats.GetSpellDamage());
//                ++i;
//            }
//        }
//        else
//        {
//            return false;
//        }
//    }
//
//    //TODO:
//    //Get these values from Lua/Text file
//    Sabotage() : Skill()
//    {
//        m_name = "Sabotage";
//        m_dmg_multi = 1.7;
//        m_mana_cost = 150;
//        m_max_target_num = 1;
//        m_ally_targetable = false;
//        m_enemy_targetable = true;
//    };
//    ~Sabotage(){};
//};