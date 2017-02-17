#include "OverworldAsset.h"

// Graphics includes
#include "GraphicsManager.h"
#include "RenderHelper.h"

OverworldAsset::OverworldAsset(const string& meshName) :
camera(nullptr), AssetEntity(meshName),
rotX(0.f),
rotZ(0.f)
{

}


OverworldAsset::~OverworldAsset()
{
}

void OverworldAsset::Update()
{
	rotX = camera->GetRotX();
	rotZ = camera->GetRotZ();
}

void OverworldAsset::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Rotate(rotZ, 0.f, 0.f, 1.f);
	modelStack.Translate(0.f, -scale.y * 0.5f, 0.f);
	modelStack.Rotate(rotX, 1.f, 0.f, 0.f);
	modelStack.Translate(0.f, scale.y * 0.5f, 0.f);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderMesh(mesh);
	modelStack.PopMatrix();
}

void OverworldAsset::HandleCollision(EntityBase* entity)
{
	return;
}
