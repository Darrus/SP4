#ifndef BATTLELOG_H
#define BATTLELOG_H

#include <list>

#include "Entity\BattleEntity.h"
#include "Player\Player.h"

class BattleLog : public BattleEntity
{
private:
    BattleEntity* entity_;
    CharacterInfo* m_entity_;
    std::string enemyname_, skillname_;
    float displayTime;
    int damagereceived_, damagedealt_;
    bool DMGRecv, DMGDeal, dodged_, critical_, defend_;
    bool playerRender, enemyRender;
    bool escapeAttempt_;
    bool AoEAnot_, manaNotEnough_;

public:
    BattleLog();
    BattleLog(BattleEntity* entity, std::string enemyname, int damagedealt, int damagereceived, bool dodged, bool critical);
    BattleLog(CharacterInfo* entity, std::string skillname, std::string targetname, bool AoEAnot);
    BattleLog(CharacterInfo* entity, bool manaNotEnough);
    BattleLog(BattleEntity* entity, bool defend);
    BattleLog(bool escapeAttempt);
    ~BattleLog();

    void Render();
    void Update();
    std::list<BattleLog*> battleloglist;

    enum ACTION
    {

    };
};

#endif /* BATTLELOG_H */