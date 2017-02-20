#include "TriggerArea.h"

#include "OverworldEntity.h"
#include "SceneManager.h"


TriggerArea::TriggerArea() :
trigger(false)
{
}


TriggerArea::~TriggerArea()
{
}

void TriggerArea::Update()
{
	if (trigger && camera->GetState() == CameraFollow::CAMERA_STATE::IDLE)
		SceneManager::GetInstance()->SetActiveScene(targetScene);
}

void TriggerArea::HandleCollision(EntityBase* entity)
{
	OverworldEntity* player = dynamic_cast<OverworldEntity*>(entity);
	if (player)
	{
		camera->Transition(0.f, 360.f, 1.f);
		camera->SetDistSpeed(100.f);
		camera->SetRotSpeed(350.f);
		trigger = true;
	}
}