#ifndef MONSTERFACTORY_H
#define MONSTERFACTORY_H

#include "Enemy.h"
#include "..\Application.h"

class MonsterFactory
{
private:
    int currID;
    int avgLvl;
public:
    MonsterFactory();
    ~MonsterFactory();

    Enemy* CreateEnemy1(int id);
    Enemy* CreateEnemy2(int id);
    Enemy* CreateEnemy3(int id);
    Enemy* CreateBoss(int id);
    Enemy* CreateRandomEnemy(int id);
    void LevelSync();

    float windowWidth = (float)Application::GetInstance().GetWindowWidth();
    float windowHeight = (float)Application::GetInstance().GetWindowHeight();
};

#endif /* MONSTERFACTORY_H */