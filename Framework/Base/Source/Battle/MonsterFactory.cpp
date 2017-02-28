#include "MonsterFactory.h"
#include "..\Player\Player.h"

MonsterFactory::MonsterFactory() :
currID(0),
avgLvl(0)
{
    for (int i = 0; i < (Player::GetInstance().GetParty()->memberCount() - 1); ++i)
    {
        avgLvl += Player::GetInstance().GetParty()->GetMember(i)->stats.Getlevel();
    }
    avgLvl /= (Player::GetInstance().GetParty()->memberCount() - 1);
}

MonsterFactory::~MonsterFactory()
{

}

EnemyInfo* MonsterFactory::CreateEnemy1(int id)
{
    LevelSync();
    EnemyInfo* newEnemy = new EnemyInfo("Carbonara");

    newEnemy->stats.AddVit(1);
    newEnemy->stats.AddStr(1);
    newEnemy->stats.AddInt(3);
    newEnemy->stats.AddMind(2);
    newEnemy->stats.AddDex(1);
    newEnemy->stats.AddAgi(3);
    newEnemy->stats.AddLevel(avgLvl);
    newEnemy->name = "Carbonara";
    newEnemy->id = id;
    newEnemy->stats.UpdateStats();
    newEnemy->HP = newEnemy->stats.GetMaxHP();
    newEnemy->MP = newEnemy->stats.GetMaxMP();

    return newEnemy;
}

EnemyInfo* MonsterFactory::CreateEnemy2(int id)
{
    LevelSync();
    EnemyInfo* newEnemy = new EnemyInfo("Kayne West");

    newEnemy->stats.AddVit(2);
    newEnemy->stats.AddStr(3);
    newEnemy->stats.AddInt(1);
    newEnemy->stats.AddMind(2);
    newEnemy->stats.AddDex(8);
    newEnemy->stats.AddAgi(10);
    newEnemy->stats.AddLevel(avgLvl);
    newEnemy->name = "Kayne West";
    newEnemy->id = id;
    //newEnemy->enemyType = BattleEntity::ENEMY;
    newEnemy->stats.UpdateStats();
    //newEnemy->SetPosition(Vector3(windowWidth * 0.25f, windowHeight * (0.15f * id), 1.f));
    newEnemy->HP = newEnemy->stats.GetMaxHP();
    newEnemy->MP = newEnemy->stats.GetMaxMP();

    return newEnemy;
}

EnemyInfo* MonsterFactory::CreateEnemy3(int id)
{
    LevelSync();
    EnemyInfo* newEnemy = new EnemyInfo("Dwayne Johnson");

    newEnemy->stats.AddVit(1);
    newEnemy->stats.AddStr(2);
    newEnemy->stats.AddInt(2);
    newEnemy->stats.AddMind(5);
    newEnemy->stats.AddDex(4);
    newEnemy->stats.AddAgi(4);
    newEnemy->stats.AddLevel(avgLvl);
    newEnemy->name = "Dwayne Johnson";
    newEnemy->id = id;
    newEnemy->stats.UpdateStats();
    newEnemy->HP = newEnemy->stats.GetMaxHP();
    newEnemy->MP = newEnemy->stats.GetMaxMP();

    return newEnemy;
}

EnemyInfo* MonsterFactory::CreateBoss(int id)
{
    LevelSync();
    EnemyInfo* newEnemy = new EnemyInfo("Alishpata");

    newEnemy->stats.AddVit(2);
    newEnemy->stats.AddStr(2);
    newEnemy->stats.AddInt(2);
    newEnemy->stats.AddMind(5);
    newEnemy->stats.AddDex(7);
    newEnemy->stats.AddAgi(10);
    newEnemy->stats.AddLevel(avgLvl + 2);
    newEnemy->name = "Alishpata";
    newEnemy->id = id;
    newEnemy->stats.UpdateStats();
    newEnemy->HP = newEnemy->stats.GetMaxHP();
    newEnemy->MP = newEnemy->stats.GetMaxMP();

    return newEnemy;
}

EnemyInfo* MonsterFactory::CreateRandomEnemy(int id)
{
    int randChoice = Math::RandIntMinMax(1, 3);
    if (randChoice >= 4)
        randChoice = Math::RandIntMinMax(1, 3);

    if (randChoice == 1)
        return CreateEnemy1(id);
    if (randChoice == 2)
        return CreateEnemy2(id);
    if (randChoice == 3)
        return CreateEnemy3(id);
}

void MonsterFactory::LevelSync()
{
    for (int i = 0; i < (Player::GetInstance().GetParty()->memberCount() - 1); ++i)
    {
        avgLvl += Player::GetInstance().GetParty()->GetMember(i)->stats.Getlevel();
    }
    avgLvl /= (Player::GetInstance().GetParty()->memberCount() - 1);
}