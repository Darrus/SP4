#include "SkyBoxEntity.h"
#include "MeshBuilder.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"

SkyBoxEntity::SkyBoxEntity(void)
	: size(1000.0f, 1000.0f, 1000.0f)
	, m_bBoundaryDefined(false)
{
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
		modelStack.PushMatrix();
		modelStack.Translate(0, size.y * 0.5f, 0.f);
		modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
		modelStack.Scale(size.x, size.y, size.z);
		RenderHelper::RenderMesh(modelMesh[FRONT]);
		modelStack.PopMatrix();

		// Front
		modelStack.PushMatrix();
		modelStack.Translate(0, -size.y * 0.5f, 0.f);
		modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
		modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
		modelStack.Scale(size.x, size.y, size.z);
		RenderHelper::RenderMesh(modelMesh[BACK]);
		modelStack.PopMatrix();

		// Right
		modelStack.PushMatrix();
		modelStack.Translate(size.x * 0.5f, 0.f, 0.f);
		modelStack.Rotate(-90.f, 0.f, 0.f, 1.f);
		modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
		modelStack.Scale(size.x, size.y, size.z);
		RenderHelper::RenderMesh(modelMesh[RIGHT]);
		modelStack.PopMatrix();

		// Left
		modelStack.PushMatrix();
		modelStack.Translate(-size.x * 0.5f, 0.f, 0.f);
		modelStack.Rotate(90.f, 0.f, 0.f, 1.f);
		modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
		modelStack.Scale(size.x, size.y, size.z);
		RenderHelper::RenderMesh(modelMesh[LEFT]);
		modelStack.PopMatrix();


	modelStack.PopMatrix();
}

// Set a mesh to this class
void SkyBoxEntity::SetMesh(const int _side, Mesh* _modelMesh)
{
	modelMesh[_side] = _modelMesh;
}

Vector3 SkyBoxEntity::GetBoundary(void)
{
	if (!m_bBoundaryDefined)
	{
		boundary = Vector3(	position.x - (size.x*scale.x) / 2.0f,
							position.y - (size.y*scale.y) / 2.0f,
							position.z - (size.z*scale.z) / 2.0f);
		m_bBoundaryDefined = true;
	}
	return boundary;
};