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

Enemy* MonsterFactory::CreateEnemy1(int id)
{
    LevelSync();
    Enemy* newEnemy = new Enemy();

    newEnemy->GetInfo()->stats.AddVit(avgLvl);
    newEnemy->GetInfo()->stats.AddStr(8);
    newEnemy->GetInfo()->stats.AddInt(5);
    newEnemy->GetInfo()->stats.AddMind(2);
    newEnemy->GetInfo()->stats.AddDex(1);
    newEnemy->GetInfo()->stats.AddAgi(7);
    newEnemy->GetInfo()->stats.AddLevel(avgLvl);
    newEnemy->GetInfo()->name = "Triple H";
    newEnemy->GetInfo()->id = id;
    newEnemy->enemyType = BattleEntity::ENEMY;
    newEnemy->GetInfo()->stats.UpdateStats();
    newEnemy->SetPosition(Vector3(windowWidth * 0.25f, windowHeight * (0.15f * id), 1.f));
    newEnemy->GetInfo()->HP = newEnemy->GetInfo()->stats.GetMaxHP();

    newEnemy->AddStats(newEnemy->GetInfo()->stats);

    return newEnemy;
}

Enemy* MonsterFactory::CreateEnemy2(int id)
{
    LevelSync();
    Enemy* newEnemy = new Enemy();

    newEnemy->GetInfo()->stats.AddVit(avgLvl);
    newEnemy->GetInfo()->stats.AddStr(3);
    newEnemy->GetInfo()->stats.AddInt(1);
    newEnemy->GetInfo()->stats.AddMind(2);
    newEnemy->GetInfo()->stats.AddDex(8);
    newEnemy->GetInfo()->stats.AddAgi(10);
    newEnemy->GetInfo()->stats.AddLevel(avgLvl);
    newEnemy->GetInfo()->name = "Kayne West";
    newEnemy->GetInfo()->id = id;
    newEnemy->enemyType = BattleEntity::ENEMY;
    newEnemy->GetInfo()->stats.UpdateStats();
    newEnemy->SetPosition(Vector3(windowWidth * 0.25f, windowHeight * (0.15f * id), 1.f));
    newEnemy->GetInfo()->HP = newEnemy->GetInfo()->stats.GetMaxHP();

    return newEnemy;
}

Enemy* MonsterFactory::CreateEnemy3(int id)
{
    LevelSync();
    Enemy* newEnemy = new Enemy();

    newEnemy->GetInfo()->stats.AddVit(avgLvl);
    newEnemy->GetInfo()->stats.AddStr(2);
    newEnemy->GetInfo()->stats.AddInt(2);
    newEnemy->GetInfo()->stats.AddMind(5);
    newEnemy->GetInfo()->stats.AddDex(12);
    newEnemy->GetInfo()->stats.AddAgi(10);
    newEnemy->GetInfo()->stats.AddLevel(avgLvl);
    newEnemy->GetInfo()->name = "Dwayne Johnson";
    newEnemy->GetInfo()->id = id;
    newEnemy->enemyType = BattleEntity::ENEMY;
    newEnemy->GetInfo()->stats.UpdateStats();
    newEnemy->SetPosition(Vector3(windowWidth * 0.25f, windowHeight * (0.15f * id), 1.f));
    newEnemy->GetInfo()->HP = newEnemy->GetInfo()->stats.GetMaxHP() * 0.2;

    return newEnemy;
}

Enemy* MonsterFactory::CreateBoss(int id)
{
    LevelSync();
    Enemy* newEnemy = new Enemy();

    newEnemy->GetInfo()->stats.AddVit(2);
    newEnemy->GetInfo()->stats.AddStr(2);
    newEnemy->GetInfo()->stats.AddInt(2);
    newEnemy->GetInfo()->stats.AddMind(5);
    newEnemy->GetInfo()->stats.AddDex(7);
    newEnemy->GetInfo()->stats.AddAgi(10);
    newEnemy->GetInfo()->stats.AddLevel(avgLvl + 5);
    newEnemy->GetInfo()->name = "Alishpata";
    newEnemy->GetInfo()->id = id;
    newEnemy->enemyType = BattleEntity::BOSS;
    newEnemy->GetInfo()->stats.UpdateStats();
    newEnemy->SetPosition(Vector3(windowWidth * 0.25f, windowHeight * (0.15f * id), 1.f));
    newEnemy->GetInfo()->HP = newEnemy->GetInfo()->stats.GetMaxHP() * 0.2;

    return newEnemy;
}

void MonsterFactory::LevelSync()
{
    for (int i = 0; i < (Player::GetInstance().GetParty()->memberCount() - 1); ++i)
    {
        avgLvl += Player::GetInstance().GetParty()->GetMember(i)->stats.Getlevel();
    }
    avgLvl /= (Player::GetInstance().GetParty()->memberCount() - 1);
}

Enemy* MonsterFactory::CreateRandomEnemy(int id)
{
    int randChoice = Math::RandIntMinMax(1, 10);
    if (randChoice >= 4)
        randChoice = Math::RandIntMinMax(1, 3);

    if (randChoice == 1)
        return CreateEnemy1(id);
    if (randChoice == 2)
        return CreateEnemy2(id);
    if (randChoice == 3)
        return CreateEnemy3(id);
}