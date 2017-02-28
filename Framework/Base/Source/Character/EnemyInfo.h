#ifndef ENEMY_INFO
#define ENEMY_INFO

#include <list>

#include "InfoBase.h"
#include "../Skills/Skill.h"

#include "MeshBuilder.h"
#include "../Application.h"

using std::list;

class EnemyInfo : public InfoBase
{
public:
    EnemyInfo(){}
    EnemyInfo(string name)
    {
        mesh = MeshBuilder::GetInstance()->GetMesh(name);
    }
    virtual ~EnemyInfo(){}

	// List of entity's skills
	typedef list<Skill*> SkillList;
	SkillList skills;

	Mesh* mesh;
};

#endif