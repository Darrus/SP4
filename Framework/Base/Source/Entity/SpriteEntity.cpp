#include "SpriteEntity.h"
#include "MeshBuilder.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"

SpriteEntity::SpriteEntity(Mesh* _modelMesh) :
modelMesh(_modelMesh),
position(0.0f, 0.0f, 0.0f),
scale(1.0f, 1.0f, 1.0f),
mode(MODE_2D)
{
	bRender = true;
}

SpriteEntity::~SpriteEntity()
{
}

void SpriteEntity::Update(double _dt)
{
	// Does nothing here, can inherit & override or create your own version of this class :D
}

void SpriteEntity::Render()
{
	if (mode == MODE_2D)
		return;

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderMesh(modelMesh);
	modelStack.PopMatrix();
}

void SpriteEntity::RenderUI()
{
	if (mode == MODE_3D)
		return;

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderMesh(modelMesh);
	modelStack.PopMatrix();
}