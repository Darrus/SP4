#include "TriggerArea.h"

#include "OverworldEntity.h"
#include "SceneManager.h"


TriggerArea::TriggerArea()
{
}


TriggerArea::~TriggerArea()
{
}

void TriggerArea::HandleCollision(EntityBase* entity)
{
	OverworldEntity* player = dynamic_cast<OverworldEntity*>(entity);
	//SceneManager::GetInstance()->SetActiveScene(targetScene);
}