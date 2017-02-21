#ifndef ENEMY_H
#define ENEMY_H

#include <list>

#include "..\Entity\BattleEntity.h"
#include "..\Skills\Skill.h"

class Enemy : public BattleEntity
{
    
private:
    std::list<Skill*> skills_;

public:
    Enemy();
    ~Enemy();
    void AddStats(StatSystem* stats);
    
    void addSkills(Skill* skills);

};

#endif