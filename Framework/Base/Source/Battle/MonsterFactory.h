#ifndef MONSTERFACTORY_H
#define MONSTERFACTORY_H

#include "Enemy.h"
#include "..\Application.h"

class MonsterFactory
{
private:
    int currID;
public:
    MonsterFactory();
    ~MonsterFactory();

    Enemy* CreateEnemy1(int id);
    Enemy* CreateEnemy2(int id);
    Enemy* CreateEnemy3(int id);
    Enemy* CreateRandomEnemy(int id);

    float windowWidth = Application::GetInstance().GetWindowWidth();
    float windowHeight = Application::GetInstance().GetWindowHeight();
};

#endif /* MONSTERFACTORY_H */