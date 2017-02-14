#include "AssetEntity.h"

#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"

AssetEntity::AssetEntity(const string& meshName)
{
	bRender = true;
	mesh = MeshBuilder::GetInstance()->GetMesh(meshName);
}


AssetEntity::~AssetEntity()
{
}

void AssetEntity::Update()
{

}

void AssetEntity::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderMesh(mesh);
	modelStack.PopMatrix();
}

void AssetEntity::RenderUI()
{

}
