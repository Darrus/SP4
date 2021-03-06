#include "MonsterFactory.h"
#include "..\Player\Player.h"

MonsterFactory::MonsterFactory() :
currID(0),
avgLvl(0)
{
   /* for (int i = 0; i < (Player::GetInstance().GetParty()->memberCount()); ++i)
    {
		avgLvl += Player::GetInstance().GetParty()->GetMemberByIndex(i)->stats.Getlevel();
    }
    avgLvl /= (Player::GetInstance().GetParty()->memberCount());*/
}

MonsterFactory::~MonsterFactory()
{

}

EnemyInfo* MonsterFactory::CreateEnemy1(int id)
{
    LevelSync();
    EnemyInfo* newEnemy = new EnemyInfo("Carbonara");
    newEnemy->stats.SetVit(6);
    newEnemy->stats.SetStr(7);
    newEnemy->stats.SetInt(3);
    newEnemy->stats.SetMind(2);
    newEnemy->stats.SetDex(6);
    newEnemy->stats.SetAgi(4);
    newEnemy->stats.AddLevel(avgLvl);
    newEnemy->name = "Big Fish";
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
    newEnemy->stats.SetVit(4);
    newEnemy->stats.SetStr(7);
    newEnemy->stats.SetInt(1);
    newEnemy->stats.SetMind(2);
    newEnemy->stats.SetDex(8);
	newEnemy->stats.SetAgi(4);
    newEnemy->stats.AddLevel(avgLvl);
    newEnemy->name = "Overlord";
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
    newEnemy->stats.SetVit(10);
    newEnemy->stats.SetStr(5);
    newEnemy->stats.SetInt(2);
    newEnemy->stats.SetMind(5);
    newEnemy->stats.SetDex(4);
    newEnemy->stats.AddAgi(5);
    newEnemy->stats.AddLevel(avgLvl);
    newEnemy->name = "Golem";
    newEnemy->id = id;
    newEnemy->stats.UpdateStats();
    newEnemy->HP = newEnemy->stats.GetMaxHP();
    newEnemy->MP = newEnemy->stats.GetMaxMP();

    return newEnemy;
}

EnemyInfo* MonsterFactory::CreateBoss(int id)
{
    LevelSync();
    EnemyInfo* newEnemy = new EnemyInfo("Goddess");
    newEnemy->stats.SetVit(10);
    newEnemy->stats.SetStr(12);
    newEnemy->stats.SetInt(10);
    newEnemy->stats.SetMind(9);
    newEnemy->stats.SetDex(15);
    newEnemy->stats.SetAgi(10);
    newEnemy->stats.AddLevel(avgLvl + 15);
    newEnemy->name = "Goddess";
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
		avgLvl += Player::GetInstance().GetParty()->GetMemberByIndex(i)->stats.Getlevel();
    }
    avgLvl /= (Player::GetInstance().GetParty()->memberCount());
}