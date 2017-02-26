#include "SkyBoxEntity.h"
#include "MeshBuilder.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"

SkyBoxEntity::SkyBoxEntity(void)
{
	for (int i = 0; i < NUM_SIDES; ++i)
	{
		modelMesh[i] = nullptr;
	}
}

SkyBoxEntity::~SkyBoxEntity()
{
}

void SkyBoxEntity::Update(double _dt)
{
	// Does nothing here, can inherit & override or create your own version of this class :D
}

void SkyBoxEntity::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();

		// Front
	if (modelMesh[FRONT])
	{
		modelStack.PushMatrix();
		modelStack.Translate(position.x, position.y + scale.y * 0.5f - 1.f, position.z);
		modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
		modelStack.Scale(scale.x, scale.y, scale.z);
		RenderHelper::RenderMesh(modelMesh[FRONT]);
		modelStack.PopMatrix();
	}

	// Back
	if (modelMesh[BACK])
	{
		modelStack.PushMatrix();
		modelStack.Translate(position.x, position.y - scale.y * 0.5f + 1.f, position.z);
		modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
		modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
		modelStack.Scale(scale.x, scale.y, scale.z);
		RenderHelper::RenderMesh(modelMesh[BACK]);
		modelStack.PopMatrix();
	}

	// Right
	if (modelMesh[RIGHT])
	{
		modelStack.PushMatrix();
		modelStack.Translate(position.x + scale.x * 0.5f - 1.f, position.y, position.z);
		modelStack.Rotate(-90.f, 0.f, 0.f, 1.f);
		modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
		modelStack.Scale(scale.x, scale.y, scale.z);
		RenderHelper::RenderMesh(modelMesh[RIGHT]);
		modelStack.PopMatrix();
	}

	// Left
	if (modelMesh[LEFT])
	{
		modelStack.PushMatrix();
		modelStack.Translate(position.x - scale.x * 0.5f + 1.f, position.y, position.z);
		modelStack.Rotate(90.f, 0.f, 0.f, 1.f);
		modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
		modelStack.Scale(scale.x, scale.y, scale.z);
		RenderHelper::RenderMesh(modelMesh[LEFT]);
		modelStack.PopMatrix();
	}
	

	// Bottom
	if (modelMesh[BOTTOM])
	{
		modelStack.PushMatrix();
		modelStack.Translate(position.x, position.y, position.z + scale.z * 0.5f);
		modelStack.Scale(scale.x, scale.y, scale.z);
		RenderHelper::RenderMesh(modelMesh[BOTTOM]);
		modelStack.PopMatrix();
	}


	modelStack.PopMatrix();
}

// Set a mesh to this class
void SkyBoxEntity::SetMesh(const int _side, Mesh* _modelMesh)
{
	modelMesh[_side] = _modelMesh;
}