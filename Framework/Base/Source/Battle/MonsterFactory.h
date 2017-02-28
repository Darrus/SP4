#ifndef MONSTERFACTORY_H
#define MONSTERFACTORY_H

#include "..\Character\EnemyInfo.h"
#include "..\Application.h"

class MonsterFactory
{
private:
    int currID;
    int avgLvl;
public:
    MonsterFactory();
    ~MonsterFactory();

    EnemyInfo* CreateEnemy1(int id);
    EnemyInfo* CreateEnemy2(int id);
    EnemyInfo* CreateEnemy3(int id);
    EnemyInfo* CreateBoss(int id);
    EnemyInfo* CreateRandomEnemy(int id);
    void LevelSync();

    float windowWidth = (float)Application::GetInstance().GetWindowWidth();
    float windowHeight = (float)Application::GetInstance().GetWindowHeight();
};

#endif /* MONSTERFACTORY_H */