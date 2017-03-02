#ifndef STAT_H
#define STAT_H

#define STAT_PER_LEVEL 5;
#define SKILL_PER_LEVEL 1;
#define HP_MULTIPLIER 50
#define MP_MULTIPLIER 20
#define DAMAGE_MULTIPLIER 10
#define SPELL_DAMAGE_MULTIPLIER 10
#define DEFENCE_MULTIPLIER 5
#define MAX_EXP_MULTIPLIER 10
#define CRIT_RATE_MULTIPLIER 0.5f
#define DODGE_RATE_MULTIPLIER 0.2f
#define RECHARGE_RATE_MULTIPLIER 1

#include "MyMath.h"

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

	void RandomStat()
	{
		int stats[6] = { 0 };
		int sum = 0;
		for (int i = 0; i < 6; ++i)
		{
			stats[i] = Math::RandIntMinMax(0, main.StatPoints);
			sum += stats[i];
		}

		int container[6] = { 0 };
		int leftOver = 0;
		for (int i = 0; i < 6; ++i)
		{
			container[i] = (int)(((float)stats[i] / (float)sum) * (float)main.StatPoints);
			leftOver += container[i];
		}
		leftOver = main.StatPoints - leftOver;
		if (leftOver > 0)
		{
			container[5] += leftOver;
		}

		AddStr(container[0]);
		AddVit(container[1]);
		AddInt(container[2]);
		AddMind(container[3]);
		AddDex(container[4]);
		AddAgi(container[5]);
		UpdateStats();
	}

public:
    StatSystem(){}
    ~StatSystem(){}
	
	void AddLevel(int amt) 
	{ 
		main.Level += amt; 
		main.StatPoints += amt * STAT_PER_LEVEL; 
		main.SkillPoints += amt * SKILL_PER_LEVEL;
		RandomStat();
	}
	void AddStr(int amt){ if (main.StatPoints > 0) { main.Str += amt; DeductStatPoint(amt); } }
	void AddVit(int amt){ if (main.StatPoints > 0) { main.Vit += amt; DeductStatPoint(amt); } }
	void AddInt(int amt){ if (main.StatPoints > 0) { main.Int += amt; DeductStatPoint(amt); } }
	void AddMind(int amt){ if (main.StatPoints > 0) { main.Mind += amt; DeductStatPoint(amt); } }
	void AddDex(int amt){ if (main.StatPoints > 0) { main.Dex += amt; DeductStatPoint(amt); } }
	void AddAgi(int amt){ if (main.StatPoints > 0) { main.Agi += amt; DeductStatPoint(amt); } }
	void AddStatPoint(int amt) { main.StatPoints += amt; }
	void AddSkillPoint(int amt) { main.SkillPoints += amt; }

    inline void SetStr(int amt){main.Str = amt; }
    inline void SetVit(int amt){ main.Vit = amt; }
    inline void SetInt(int amt){ main.Int = amt; }
    inline void SetMind(int amt){ main.Mind = amt; }
    inline void SetDex(int amt){ main.Dex = amt; }
    inline void SetAgi(int amt){ main.Agi = amt; }
    inline void SetStatPoint(int amt) { main.StatPoints = amt; }
    inline void SetSkillPoint(int amt) { main.SkillPoints = amt; }

	void DeductLevel(int amt) { main.Level -= amt; main.StatPoints += amt; }
	void DeductStr(int amt){ if (main.Str > 0) { main.Str -= amt; main.StatPoints += amt;} }
	void DeductVit(int amt){ if (main.Vit > 0) { main.Vit -= amt; main.StatPoints += amt; } }
	void DeductInt(int amt){ if (main.Int > 0) { main.Int -= amt; main.StatPoints += amt; } }
	void DeductMind(int amt){ if (main.Mind > 0) { main.Mind -= amt; main.StatPoints += amt; } }
	void DeductDex(int amt){ if (main.Dex > 0) { main.Dex -= amt; main.StatPoints += amt; } }
	void DeductAgi(int amt){ if (main.StatPoints) { main.Agi -= amt; main.StatPoints += amt; } }
	void DeductStatPoint(int amt) { main.StatPoints -= amt;}
	void DeductSkillPoints(int amt) { main.SkillPoints -= amt;}

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
    inline void AddDefence(int amt) { sub.Defence += amt; }
    inline void AddDodgeRate(int amt){ sub.DodgeRate += amt; }
    inline void AddCritRate(int amt) { sub.CritRate += amt; }
    inline void AddRechargeRate(int amt){ sub.RechargeRate += amt; }
    inline void AddMaxHP(int amt) { sub.MaxHP += amt; }
    inline void AddMaxMP(int amt){ sub.MaxMP += amt; }

    inline void DeductDamage(int amt) { sub.Damage -= amt; }
    inline void DeductSpellDamage(int amt){ sub.SpellDamage -= amt; }
    inline void DeductDefence(int amt) { sub.Defence -= amt; }
    inline void DeductDodgeRate(int amt){ sub.DodgeRate -= amt; }
    inline void DeductCritRate(int amt) { sub.CritRate -= amt; }
    inline void DeductRechargeRate(int amt){ sub.RechargeRate -= amt; }
    inline void DeductMaxHP(int amt) { sub.MaxHP -= amt; }
    inline void DeductMaxMP(int amt){ sub.MaxMP -= amt; }

    inline void SetRechargeRate(int amt){ sub.RechargeRate = amt; }

	void UpdateStats()
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