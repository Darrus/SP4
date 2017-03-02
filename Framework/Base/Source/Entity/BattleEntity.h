#ifndef BATTLE_ENTITY_H
#define BATTLE_ENTITY_H

#include "EntityBase.h"
#include "../Character/InfoBase.h"

class BattleEntity : public EntityBase
{
    InfoBase* info;
    const float maxATB;
    float ATB;

    bool isDead;
    bool isReady;
    float defendRatio;
    char AttkTurnPt;

public:
	int id;

    BattleEntity();
    virtual ~BattleEntity();

    virtual void Update();


    bool GetReady() { return isReady; }
    bool GetDead() { return isDead; }
    InfoBase* GetInfo() { return info; }
    int GetDamage();
    int GetHP();
    void TakeDamage(int damage);
    float GetATB() { return ATB; }
    void SetATB(float ATB) { this->ATB = ATB; }
    void SetReady(bool ready) { isReady = ready; }
    void SetDefending(float def) { defendRatio = def; }
    float GetDefending() { return defendRatio; }

    char GetAttkTurnPt() { return AttkTurnPt; }
    void AddAttkTurnPt(char pt) { AttkTurnPt += pt; }
    void DecreaseAttkTurnPt(char pt) { AttkTurnPt -= pt; }
    void SetInfo(InfoBase* info_) { info = info_; }

    enum ENEMYTYPE
    {
        ENEMY = 0,
        ALLY,
        BOSS
    };

    ENEMYTYPE enemyType;
};

#endif