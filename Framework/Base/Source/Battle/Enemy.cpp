#include "Enemy.h"
#include "../Application.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::AddStats(StatSystem stats)
{
    float windowWidth = Application::GetInstance().GetWindowWidth();
    float windowHeight = Application::GetInstance().GetWindowHeight();

    BattleEntity* stuff = new BattleEntity;
    stuff->GetInfo()->stats = stats;
    stuff->enemyType = BattleEntity::ENEMY;
    stuff->GetInfo()->stats.UpdateStats();
    stuff->SetPosition(Vector3(windowWidth * 0.25f, windowHeight * (0.15f * stuff->GetInfo()->id), 1.f));
    stuff->GetInfo()->HP = stuff->GetInfo()->stats.GetMaxHP();
}

void Enemy::addSkills(Skill* skills)
{
    skills_.push_back(skills);
}