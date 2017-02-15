#include "OverworldAsset.h"

// Graphics includes
#include "GraphicsManager.h"
#include "RenderHelper.h"

OverworldAsset::OverworldAsset(const string& meshName) :
camera(nullptr), AssetEntity(meshName),
rotX(0.f),
rotY(0.f),
battle(false)
{

}


OverworldAsset::~OverworldAsset()
{
}

void OverworldAsset::Update()
{
	Vector3 cameraPos = camera->GetCameraPos();
	rotX = atan2(-cameraPos.y, cameraPos.z);
	rotY = atan2(cameraPos.x * cos(rotX), cameraPos.z);

	rotX = Math::RadianToDegree(rotX);
	rotY = Math::RadianToDegree(rotY);
}

void OverworldAsset::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Rotate(rotX, 1.f, 0.f, 0.f);
	modelStack.Translate(0.f, scale.y * 0.5f, 0.f);
	if (battle)
		modelStack.Rotate(rotY, 0.f, 1.f, 0.f);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderMesh(mesh);
	modelStack.PopMatrix();
}