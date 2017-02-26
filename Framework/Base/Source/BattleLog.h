#ifndef BATTLELOG_H
#define BATTLELOG_H

#include <list>

#include "Entity\BattleEntity.h"
#include "Player\Player.h"

class BattleLog : public BattleEntity
{
private:
    bool DMGRecv, DMGDeal, dodged_, critical_, defend_;
    BattleEntity* entity_;
    std::string enemyname_;
    int damagereceived_, damagedealt_;
    float displayTime;
    bool playerRender, enemyRender;
    CharacterInfo* m_entity_;
public:
    BattleLog();
    BattleLog(BattleEntity* entity, std::string enemyname, int damagedealt, int damagereceived, bool dodged, bool critical);
    BattleLog(BattleEntity* entity, bool defend);
    BattleLog(CharacterInfo* entity, std::string skillname);
    ~BattleLog();

    void Render();
    void Update();
    std::list<BattleLog*> battleloglist;

    enum ACTION
    {

    };
};

#endif /* BATTLELOG_H */