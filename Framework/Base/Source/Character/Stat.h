#ifndef STAT_H
#define STAT_H

#define HP_MULTIPLIER 50
#define MP_MULTIPLIER 20
#define DAMAGE_MULTIPLIER 10
#define SPELL_DAMAGE_MULTIPLIER 10
#define DEFENCE_MULTIPLIER 5
#define MAX_EXP_MULTIPLIER 10
#define CRIT_RATE_MULTIPLIER 0.5f
#define DODGE_RATE_MULTIPLIER 0.2f
#define RECHARGE_RATE_MULTIPLIER 1.f

struct MainStat
{
	int Str;
	int Vit;
	int Int;
	int Mind;
	int Dex;
	int Agi;
	int Level;
	int statPoints;
};

struct SubStat
{
	int Damage;
	int SpellDamage;
	int MaxHP;
	int MaxMP;
	int MaxEXP;
	int Defence;
	float DodgeRate;
	float CritRate;
	float RechargeRate;
};

class StatSystem
{
	MainStat main;
	SubStat sub;

public:
	StatSystem();
	~StatSystem();
	
	inline void AddLevel(int amt) { main.Level += amt; }
	inline void AddStr(int amt){ main.Str += amt; }
	inline void AddVit(int amt){ main.Vit += amt; }
	inline void AddInt(int amt){ main.Int += amt; }
	inline void AddMind(int amt){ main.Mind += amt; }
	inline void AddDex(int amt){ main.Dex += amt; }
	inline void AddAgi(int amt){ main.Agi += amt; }
	inline void AddStatPoint(int amt) { main.statPoints += amt; }

	inline void DeductLevel(int amt) { main.Level -= amt; }
	inline void DeductStr(int amt){ main.Str -= amt; }
	inline void DeductVit(int amt){ main.Vit -= amt; }
	inline void DeductInt(int amt){ main.Int -= amt; }
	inline void DeductMind(int amt){ main.Mind -= amt; }
	inline void DeductDex(int amt){ main.Dex -= amt; }
	inline void DeductAgi(int amt){ main.Agi -= amt; }
	inline void DeductStatPoint(int amt) { main.statPoints -= amt; }

	inline int Getlevel(){ return main.Level; }
	inline int GetStr(){ return main.Str; }
	inline int GetVit(){ return main.Vit; }
	inline int GetInt(){ return main.Int; }
	inline int GetMind(){ return main.Mind; }
	inline int GetDex(){ return main.Dex; }
	inline int GetAgi(){ return main.Agi; }
	inline int GetStatPoints(){ return main.statPoints; }

	inline int GetMaxEXP() { return sub.MaxEXP; }
	inline int GetDamage() { return sub.Damage; }
	inline int GetSpellDamage(){ return sub.SpellDamage; }
	inline int GetMaxHP() { return sub.MaxHP; }
	inline int GetMaxMP(){ return sub.MaxMP; }
	inline int GetDefence() { return sub.Defence; }
	inline float GetDodgeRate(){ return sub.DodgeRate; }
	inline float GetCritRate(){ return sub.CritRate; }
	inline float GetRechargeRate(){ return sub.RechargeRate; }

	inline void UpdateStats()
	{
		sub.MaxEXP = main.Level * MAX_EXP_MULTIPLIER;
		sub.MaxHP = (main.Vit + main.Level) * HP_MULTIPLIER;
		sub.MaxMP = (main.Mind + main.Level) * MP_MULTIPLIER;
		sub.Damage = (main.Str + main.Level) * DAMAGE_MULTIPLIER;
		sub.SpellDamage = (main.Int + main.Level) * SPELL_DAMAGE_MULTIPLIER;
		sub.Defence = (main.Vit + main.Level) * DEFENCE_MULTIPLIER;
		sub.DodgeRate = (main.Dex + main.Level) * DODGE_RATE_MULTIPLIER;
		sub.CritRate = (main.Dex + main.Level) * CRIT_RATE_MULTIPLIER;
		sub.RechargeRate = (main.Agi + main.Level) * RECHARGE_RATE_MULTIPLIER;
	}
};



#endif