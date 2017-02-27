#include "StaticAsset.h"

// Graphics includes
#include "GraphicsManager.h"
#include "RenderHelper.h"

#include "MeshBuilder.h"

StaticAsset::StaticAsset(const string& frontMeshName, const string& sideMeshName) :
OverworldAsset(frontMeshName)
{
	front = MeshBuilder::GetInstance()->GetMesh(frontMeshName);
	side = MeshBuilder::GetInstance()->GetMesh(sideMeshName);
	view.Set(0.f, -1.f, 0.f);
	rotZ = 0.f;
}


StaticAsset::~StaticAsset()
{
}

void StaticAsset::Update()
{
	float angle = camera->GetRotZ();
	if (angle <= -45 || angle >= 45)
		mesh = side;
	else
		mesh = front;
}

void StaticAsset::SetRotZ(const float& rotZ)
{
	this->rotZ = rotZ;
	Mtx44 rotation;
	rotation.SetToRotation(rotZ, 0.f, 0.f, 1.f);
	view = rotation * view;
}

void StaticAsset::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Rotate(camera->GetRotZ(), 0.f, 0.f, 1.f);
	modelStack.Translate(0.f, -scale.y * 0.5f, 0.f);
	modelStack.Rotate(camera->GetRotX(), 1.f, 0.f, 0.f);
	modelStack.Translate(0.f, scale.y * 0.5f, 0.f);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderMesh(mesh);
	modelStack.PopMatrix();
}