#ifndef STAT_H
#define STAT_H

struct MainStat
{
	int Str;
	int Vit;
	int Int;
	int Mind;
	int Dex;
	int Agi;
};

struct SubStat
{
	int Damage;
	int SpellDamage;
	int MaxHP;
	int MaxMP;
	float DodgeRate;
	float CritRate;
	float ATB_RechargeRate;
};

class StatSystem
{
	MainStat main;
	SubStat sub;

public:
	StatSystem();
	~StatSystem();

	inline void AddStr(int amt){ main.Str += amt; }
	inline void AddVit(int amt){ main.Vit += amt; }
	inline void AddInt(int amt){ main.Int += amt; }
	inline void AddMind(int amt){ main.Mind += amt; }
	inline void AddDex(int amt){ main.Dex += amt; }
	inline void AddAgi(int amt){ main.Agi += amt; }

	inline void DeductStr(int amt){ main.Str -= amt; }
	inline void DeductVit(int amt){ main.Vit -= amt; }
	inline void DeductInt(int amt){ main.Int -= amt; }
	inline void DeductMind(int amt){ main.Mind -= amt; }
	inline void DeductDex(int amt){ main.Dex -= amt; }
	inline void DeductAgi(int amt){ main.Agi -= amt; }

	inline int GetDamage() { return sub.Damage; }
	inline int GetSpellDamage(){ return sub.SpellDamage; }
	inline int GetMaxHP() { return sub.MaxHP; }
	inline int GetMaxMP(){ return sub.MaxMP; }
	inline float GetDodgeRate(){ return sub.DodgeRate; }
	inline float GetCritRate(){ return sub.CritRate; }
	inline float GetRechargeRate(){ return sub.ATB_RechargeRate; }
};



#endif