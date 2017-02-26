#include "BattleLog.h"
#include "Application.h"

#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "GraphicsManager.h"

#include "timer.h"

BattleLog::BattleLog()
{

}

BattleLog::BattleLog(BattleEntity* entity, std::string enemyname, int damagedealt, int damagereceived, bool dodged, bool critical) :
entity_(entity),
enemyname_(enemyname),
damagedealt_(damagedealt),
damagereceived_(damagereceived),
dodged_(dodged),
critical_(critical)
{
    displayTime = 3;
    if (damagereceived_ > 0)
        DMGRecv = true;
    if (damagedealt_ > 0)
        DMGDeal = true;
}

BattleLog::BattleLog(BattleEntity* entity, bool defend):
entity_(entity),
defend_(defend)
{
    displayTime = 3;
    DMGRecv = false;
    DMGDeal = false;
}

BattleLog::BattleLog(CharacterInfo* entity, std::string skillname) :
m_entity_(entity),
enemyname_(skillname)
{

    displayTime = 3;
    DMGRecv = false;
    DMGDeal = false;
}

BattleLog::~BattleLog()
{

}

void BattleLog::Update()
{
    if (displayTime > 0)
        displayTime -= StopWatch::GetInstance()->GetDeltaTime();
}

void BattleLog::Render()
{
    MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
    float windowWidth = Application::GetInstance().GetWindowWidth();
    float windowHeight = Application::GetInstance().GetWindowHeight();

    for (std::list<BattleLog*>::iterator itr = battleloglist.begin(); itr != battleloglist.end(); itr++)
    {
        if (displayTime > 0)
        {
            modelStack.PushMatrix();
            modelStack.Translate(windowWidth * 0.5, windowHeight * 0.9, 5.f);
            modelStack.Scale(windowWidth *0.4, windowHeight *0.1, 1.f);
            RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Commandselect"));
            modelStack.PopMatrix();

            if ((*itr)->DMGRecv)
            {   
                modelStack.PushMatrix();
                modelStack.Translate(windowWidth * 0.35, windowHeight * 0.9, 8);
                modelStack.Scale(25.f, 25.f, 1.f);
                if ((*itr)->critical_)
                    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*itr)->enemyname_ + " has crit for " + std::to_string((*itr)->damagedealt_) + " to " + (*itr)->entity_->GetInfo()->name, Color(0, 1, 0));
                else if ((*itr)->dodged_)
                    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*itr)->entity_->GetInfo()->name + " has dodged the atk by " + (*itr)->enemyname_, Color(0, 1, 0));
                else
                    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*itr)->enemyname_ + " has dealt " + std::to_string((*itr)->damagedealt_) + " damage to " + (*itr)->entity_->GetInfo()->name, Color(0, 1, 0));
                modelStack.PopMatrix();
            }
            else if ((*itr)->m_entity_ != nullptr)
            {
                modelStack.PushMatrix();
                modelStack.Translate(windowWidth * 0.35, windowHeight * 0.9, 8);
                modelStack.Scale(25.f, 25.f, 1.f);
                RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*itr)->m_entity_->name + " casted " + enemyname_ + "!.", Color(0, 1, 0));
                modelStack.PopMatrix();
            }
            else if ((*itr)->defend_)
            {
                modelStack.PushMatrix();
                modelStack.Translate(windowWidth * 0.35, windowHeight * 0.9, 8);
                modelStack.Scale(25.f, 25.f, 1.f);
                RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*itr)->entity_->GetInfo()->name + " defended", Color(0, 1, 0));
                modelStack.PopMatrix();
            }
        }
    }
}