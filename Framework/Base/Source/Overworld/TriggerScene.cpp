#include "TriggerScene.h"
#include "SceneManager.h"

TriggerScene::TriggerScene()
{
}


TriggerScene::~TriggerScene()
{
}

void TriggerScene::Update()
{
	if (trigger && camera->GetState() == CameraFollow::CAMERA_STATE::IDLE)
		SceneManager::GetInstance()->SetActiveScene(targetScene);
}

void TriggerScene::OnTrigger()
{
	camera->Transition(0.f, 360.f, 1.f);
	camera->SetDistSpeed(100.f);
	camera->SetRotSpeed(350.f);
}