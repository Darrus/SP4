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

    m_entity_ = nullptr;
    defend_ = false;
    manaNotEnough_ = false;
}

BattleLog::BattleLog(CharacterInfo* entity, std::string skillname, std::string targetname, bool AoEAnot) :
m_entity_(entity),
enemyname_(targetname),
skillname_(skillname),
AoEAnot_(AoEAnot)
{
    displayTime = 3;
    DMGRecv = false;
    DMGDeal = false;
    defend_ = false;
    manaNotEnough_ = false;
}

BattleLog::BattleLog(BattleEntity* entity, bool defend) :
entity_(entity),
defend_(defend)
{
    displayTime = 3;
    DMGRecv = false;
    DMGDeal = false;
    m_entity_ = nullptr;
    manaNotEnough_ = false;
}

BattleLog::BattleLog(CharacterInfo* entity, bool manaNotEnough) :
m_entity_(entity),
manaNotEnough_(manaNotEnough)
{
    displayTime = 3;
    DMGRecv = false;
    DMGDeal = false;
    m_entity_ = nullptr;
}

BattleLog::BattleLog(bool escapeAttempt) :
escapeAttempt_(escapeAttempt)
{
    displayTime = 3;
    DMGRecv = false;
    DMGDeal = false;
    m_entity_ = nullptr;
    defend_ = false;
    manaNotEnough_ = false;
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
            modelStack.Translate(windowWidth * 0.5f, windowHeight * 0.9f, 5.f);
            modelStack.Scale(windowWidth *0.4f, windowHeight *0.1f, 1.f);
            RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Commandselect"));
            modelStack.PopMatrix();

            if ((*itr)->DMGRecv)
            {
                modelStack.PushMatrix();
                modelStack.Translate(windowWidth * 0.32f, windowHeight * 0.9f, 8.f);
                modelStack.Scale(25.f, 25.f, 1.f);
                if ((*itr)->critical_)
                    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*itr)->enemyname_ + " has crit for " + std::to_string((*itr)->damagedealt_) + " to " + (*itr)->entity_->GetInfo()->name, Color(0, 1, 0));
                else if ((*itr)->dodged_)
                    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*itr)->entity_->GetInfo()->name + " has dodged the atk by " + (*itr)->enemyname_, Color(0, 1, 0));
                else
                    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*itr)->enemyname_ + " has dealt " + std::to_string((*itr)->damagedealt_) + " damage to " + (*itr)->entity_->GetInfo()->name, Color(0, 1, 0));
                modelStack.PopMatrix();
            }
            else if ((*itr)->m_entity_ != nullptr && !manaNotEnough_)
            {
                if (AoEAnot_)
                {
                    modelStack.PushMatrix();
                    modelStack.Translate(windowWidth * 0.32f, windowHeight * 0.9f, 8.f);
                    modelStack.Scale(25.f, 25.f, 1.f);
                    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*itr)->m_entity_->name + " used " + skillname_, Color(0, 1, 0));
                    modelStack.PopMatrix();
                }
                else
                {
                    modelStack.PushMatrix();
                    modelStack.Translate(windowWidth * 0.32f, windowHeight * 0.9f, 8.f);
                    modelStack.Scale(25.f, 25.f, 1.f);
                    RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*itr)->m_entity_->name + " used " + skillname_ + " on " + enemyname_, Color(0, 1, 0));
                    modelStack.PopMatrix();
                }
            }
            else if ((*itr)->manaNotEnough_)
            {
                modelStack.PushMatrix();
                modelStack.Translate(windowWidth * 0.32f, windowHeight * 0.9f, 8.f);
                modelStack.Scale(25.f, 25.f, 1.f);
                RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Not Enough Mana.", Color(0, 1, 0));
                modelStack.PopMatrix();
            }
            else if ((*itr)->defend_)
            {
                modelStack.PushMatrix();
                modelStack.Translate(windowWidth * 0.32f, windowHeight * 0.9f, 8.f);
                modelStack.Scale(25.f, 25.f, 1.f);
                RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), (*itr)->entity_->GetInfo()->name + " defended", Color(0, 1, 0));
                modelStack.PopMatrix();
            }
            else if ((*itr)->escapeAttempt_)
            {
                modelStack.PushMatrix();
                modelStack.Translate(windowWidth * 0.32f, windowHeight * 0.9f, 8);
                modelStack.Scale(25.f, 25.f, 1.f);
                RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Fled the Battle!", Color(0, 1, 0));
                modelStack.PopMatrix();
            }
            else if (!(*itr)->escapeAttempt_)
            {
                modelStack.PushMatrix();
                modelStack.Translate(windowWidth * 0.32f, windowHeight * 0.9f, 8);
                modelStack.Scale(25.f, 25.f, 1.f);
                RenderHelper::RenderText(MeshBuilder::GetInstance()->GetMesh("text"), "Failed to flee the Battle.", Color(0, 1, 0));
                modelStack.PopMatrix();
            }
        }
    }
}