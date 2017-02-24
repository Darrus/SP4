#include "StaticAsset.h"

// Graphics includes
#include "GraphicsManager.h"
#include "RenderHelper.h"

StaticAsset::StaticAsset(const string& meshName) :
OverworldAsset(meshName)
{
}


StaticAsset::~StaticAsset()
{
}

void StaticAsset::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Rotate(rotZ, 0.f, 0.f, 1.f);
	modelStack.Translate(0.f, -scale.y * 0.5f, 0.f);
	modelStack.Rotate(camera->GetRotX(), 1.f, 0.f, 0.f);
	modelStack.Translate(0.f, scale.y * 0.5f, 0.f);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderMesh(mesh);
	modelStack.PopMatrix();
}