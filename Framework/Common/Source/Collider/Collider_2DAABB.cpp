#include "Collider_2DAABB.h"
#include "../EntityBase.h"

// Graphics includes
#include "../GraphicsManager.h"
#include "../RenderHelper.h"
#include "../MeshBuilder.h"

CCollider_2DAABB::CCollider_2DAABB()
{
	type = AABB_2D;
}


CCollider_2DAABB::~CCollider_2DAABB()
{
}

void CCollider_2DAABB::RenderCollider()
{
	Vector3 position;
	if (entity)
		position = entity->GetPosition();

	position += offset;

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, 10.f);
	modelStack.Scale(scale.x, scale.y, 1.f);
	RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Collider"));
	modelStack.PopMatrix();
}

bool CCollider_2DAABB::CheckCollision(CCollider* other)
{
	CCollider_2DAABB* otherAABB;
	if (other->GetType() == AABB_2D)
		otherAABB = (CCollider_2DAABB*)other;

	Vector3 thisMin = GetMin();
	Vector3 thisMax = GetMax();
	Vector3 otherMin = otherAABB->GetMin();
	Vector3 otherMax = otherAABB->GetMax();

	return 
		(thisMin.x < otherMax.x &&
		thisMax.x > otherMin.x &&
		thisMin.y < otherMax.y &&
		thisMax.y > otherMin.y);
}

bool CCollider_2DAABB::CheckIntersection(Ray& ray)
{
	// Ray to 2D AABB code goes here.
	return false;
}

Vector3 CCollider_2DAABB::GetMin()
{
	Vector3 position;
	if (entity)
		position = entity->GetPosition();

	return Vector3((position.x + offset.x) - scale.x * 0.5f, (position.y + offset.y) - scale.y * 0.5f, 0.f);
}

Vector3 CCollider_2DAABB::GetMax()
{
	Vector3 position;
	if (entity)
		position = entity->GetPosition();

	return Vector3((position.x + offset.x) + scale.x * 0.5f, (position.y + offset.y) + scale.y * 0.5f, 0.f);
}