#ifndef STAT_H
#define STAT_H

#define STAT_PER_LEVEL 5;
#define HP_MULTIPLIER 50
#define MP_MULTIPLIER 20
#define DAMAGE_MULTIPLIER 10
#define SPELL_DAMAGE_MULTIPLIER 10
#define DEFENCE_MULTIPLIER 5
#define MAX_EXP_MULTIPLIER 10
#define CRIT_RATE_MULTIPLIER 0.5f
#define DODGE_RATE_MULTIPLIER 0.2f
#define RECHARGE_RATE_MULTIPLIER 1

struct MainStat
{
	int Level = 0;
    int Str = 0; 
	int Vit = 0;
	int Int = 0;
	int Mind = 0;
	int Dex = 0;
	int Agi = 0;
	int StatPoints = 0;
	int SkillPoints = 0;
};

struct SubStat
{
	int Damage = 0;
	int SpellDamage = 0;
	int MaxHP = 0;
	int MaxMP = 0;
	int MaxEXP = 0;
	int Defence = 0;
	float DodgeRate = 0.f;
	float CritRate = 0.f;
	float RechargeRate = 0.f;
};

class StatSystem
{
	MainStat main;
	SubStat sub;

public:
    StatSystem(){}
    ~StatSystem(){}
	
	inline void AddLevel(int amt) 
	{ 
		main.Level += amt; 
		main.StatPoints += amt * STAT_PER_LEVEL; 
	}
	inline void AddStr(int amt){ if (main.StatPoints > 0) main.Str += amt; }
	inline void AddVit(int amt){ if (main.StatPoints > 0) main.Vit += amt; }
	inline void AddInt(int amt){ if (main.StatPoints > 0) main.Int += amt; }
	inline void AddMind(int amt){ if (main.StatPoints > 0) main.Mind += amt; }
	inline void AddDex(int amt){ if (main.StatPoints > 0) main.Dex += amt; }
	inline void AddAgi(int amt){ if (main.StatPoints > 0) main.Agi += amt; }
	inline void AddStatPoint(int amt) { if (main.StatPoints > 0) main.StatPoints += amt; }
	inline void AddSkillPoint(int amt) { if (main.StatPoints > 0) main.SkillPoints += amt; }

	inline void DeductLevel(int amt) { main.Level -= amt; main.StatPoints += amt; }
	inline void DeductStr(int amt){ main.Str -= amt; main.StatPoints += amt; }
	inline void DeductVit(int amt){ main.Vit -= amt; main.StatPoints += amt; }
	inline void DeductInt(int amt){ main.Int -= amt; main.StatPoints += amt; }
	inline void DeductMind(int amt){ main.Mind -= amt; main.StatPoints += amt; }
	inline void DeductDex(int amt){ main.Dex -= amt; main.StatPoints += amt; }
	inline void DeductAgi(int amt){ main.Agi -= amt; main.StatPoints += amt; }
	inline void DeductStatPoint(int amt) { main.StatPoints -= amt; main.StatPoints += amt; }
	inline void DeductSkillPoints(int amt) { main.SkillPoints -= amt; main.StatPoints += amt; }

	inline int Getlevel(){ return main.Level; }
	inline int GetStr(){ return main.Str; }
	inline int GetVit(){ return main.Vit; }
	inline int GetInt(){ return main.Int; }
	inline int GetMind(){ return main.Mind; }
	inline int GetDex(){ return main.Dex; }
	inline int GetAgi(){ return main.Agi; }
	inline int GetStatPoints(){ return main.StatPoints; }
	inline int GetSkillPoints(){ return main.SkillPoints; }

	inline int GetMaxEXP() { return sub.MaxEXP; }
	inline int GetDamage() { return sub.Damage; }
	inline int GetSpellDamage(){ return sub.SpellDamage; }
	inline int GetMaxHP() { return sub.MaxHP; }
	inline int GetMaxMP(){ return sub.MaxMP; }
	inline int GetDefence() { return sub.Defence; }
	inline float GetDodgeRate(){ return sub.DodgeRate; }
	inline float GetCritRate(){ return sub.CritRate; }
	inline float GetRechargeRate(){ return sub.RechargeRate; }

    inline void AddDamage(int amt) { sub.Damage += amt; }
    inline void AddSpellDamage(int amt){ sub.SpellDamage += amt; }

	inline void UpdateStats()
	{
		sub.MaxEXP = main.Level * MAX_EXP_MULTIPLIER;
		sub.MaxHP = (main.Vit + main.Level) * HP_MULTIPLIER;
		sub.MaxMP = (main.Mind + main.Level) * MP_MULTIPLIER;
		sub.Damage = (main.Str + main.Level) * DAMAGE_MULTIPLIER;
		sub.SpellDamage = (main.Int + main.Level) * SPELL_DAMAGE_MULTIPLIER;
		sub.Defence = (main.Vit + main.Level) * DEFENCE_MULTIPLIER;
        sub.DodgeRate = ((float)main.Dex + (float)main.Level) * DODGE_RATE_MULTIPLIER;
        sub.CritRate = ((float)main.Dex + (float)main.Level) * CRIT_RATE_MULTIPLIER;
        sub.RechargeRate = ((float)main.Agi + (float)main.Level) * RECHARGE_RATE_MULTIPLIER;
	}
};



#endif