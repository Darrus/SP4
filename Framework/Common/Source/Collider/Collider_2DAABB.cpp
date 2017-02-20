#include "Collider_2DAABB.h"
#include "../EntityBase.h"

// Graphics includes
#include "../GraphicsManager.h"
#include "../RenderHelper.h"
#include "../MeshBuilder.h"

CCollider_2DAABB::CCollider_2DAABB() :
top(false), down(false),
left(false), right(false)
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
	modelStack.Translate(position.x, position.y, position.z + 0.1f);
	modelStack.Scale(scale.x, scale.y, 1.f);
	RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Collider"));
	modelStack.PopMatrix();
}

bool CCollider_2DAABB::CheckCollision(CCollider* other)
{
	top = down = left = right = 0.f;
	bool result = false;

	CCollider_2DAABB* otherAABB;
	if (other->GetType() == AABB_2D)
		otherAABB = (CCollider_2DAABB*)other;

	Vector3 thisMin = GetMin();
	Vector3 thisMax = GetMax();
	Vector3 otherMin = otherAABB->GetMin();
	Vector3 otherMax = otherAABB->GetMax();

	if (thisMin.x < otherMax.x &&
		thisMax.x > otherMin.x &&
		thisMin.y < otherMax.y &&
		thisMax.y > otherMin.y)
	{
		result = true;


		if (thisMin.x < otherMax.x && thisMin.x > otherMin.x && thisMax.x > otherMax.x)
			left = otherMax.x - thisMin.x;

		if (thisMax.x > otherMin.x && thisMax.x < otherMax.x && thisMin.x < otherMin.x)
			right = thisMax.x - otherMin.x;

		if (thisMin.y < otherMax.y && thisMin.y > otherMin.y && thisMax.y > otherMax.y)
			down = otherMax.y - thisMin.y;

		if (thisMax.y > otherMin.y && thisMax.y < otherMax.y && thisMin.y < otherMin.y)
			top = thisMax.y - otherMin.y;
	}

	return result;
}

bool CCollider_2DAABB::CheckCollision(const Vector3& point)
{
	Vector3 min = GetMin();
	Vector3 max = GetMax();
	return (point.x < max.x &&
		point.x > min.x &&
		point.y < max.y &&
		point.y > min.y);
}

bool CCollider_2DAABB::CheckIntersection(Ray& ray)
{
	// Ray to 2D AABB code goes here.
	return false;
}