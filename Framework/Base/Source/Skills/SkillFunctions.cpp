#include "SkillFunctions.h"

void SkillFunctions::Heal(SkillParameters *skillparam)
{
	int healValue = 10;
	skillparam->targetlist->at(0)->GetInfo()->HP += skillparam->caster->GetInfo()->stats.GetInt() * healValue;
	std::cout << "Used Heal!" << std::endl;
	std::cout << "Health healed: " << skillparam->caster->GetInfo()->stats.GetInt() * healValue << std::endl;
}

void SkillFunctions::Overpower(SkillParameters *skillparam)
{
	int attackValue = 2;
	skillparam->targetlist->at(0)->GetInfo()->HP -= skillparam->caster->GetInfo()->stats.GetStr() * attackValue;
	std::cout << "Used Overpower!" << std::endl;
	std::cout << "Damage dealt: " << skillparam->caster->GetInfo()->stats.GetStr() * attackValue << std::endl;
}