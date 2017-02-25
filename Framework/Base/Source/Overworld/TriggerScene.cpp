#include "TriggerScene.h"
#include "SceneManager.h"

#include "OverworldBase.h"

TriggerScene::TriggerScene()
{
}


TriggerScene::~TriggerScene()
{
}

void TriggerScene::Init(const string& scene, CameraFollow* camera, const Vector3& playerStartPos)
{
	targetScene = scene;
	this->camera = camera;
	startPos = playerStartPos;
}

void TriggerScene::Init(const string& scene, CameraFollow* camera)
{
	targetScene = scene;
	this->camera = camera;
}

void TriggerScene::Update()
{
	if (trigger && camera->GetState() == CameraFollow::CAMERA_STATE::IDLE)
	{
		OverworldBase* scene = (OverworldBase*)SceneManager::GetInstance()->SetActiveScene(targetScene);
		scene->SetStartPos(startPos);
		trigger = false;
	}
}

void TriggerScene::OnTrigger()
{
	if (!trigger)
	{
		camera->Transition(camera->GetRotX(), camera->GetRotZ(), 1.f);
		camera->SetDistSpeed(100.f);
		camera->SetRotSpeed(350.f);
	}
}