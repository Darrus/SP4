#include "Collider_Sphere.h"
#include "Collider_AABB.h"

#include "../MeshBuilder.h"
#include "../RenderHelper.h"
#include "../GraphicsManager.h"
#include <GL/glew.h>

CCollider_Sphere::CCollider_Sphere(EntityBase* entity) :
CCollider(entity)
{
	type = SPHERE;
}


CCollider_Sphere::~CCollider_Sphere()
{

}

void CCollider_Sphere::RenderCollider()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(GetPosition().x, GetPosition().y, GetPosition().z);
	modelStack.Scale(length, length, length);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("sphere"));
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	modelStack.PopMatrix();
}

bool CCollider_Sphere::CheckCollision(CCollider* other)
{
	switch (other->GetType())
	{
	case SPHERE:
		return CheckSphere((CCollider_Sphere*)other);
		break;
	case AABB:
		return CheckAABB((CCollider_AABB*)other);
		break;
	}

	return false;
}

bool CCollider_Sphere::CheckIntersection(Ray& ray)
{
	return false;
}

void CCollider_Sphere::SetLength(float _length)
{
	length = _length;
}

float CCollider_Sphere::GetLength() const
{
	return length;
}

bool CCollider_Sphere::CheckSphere(CCollider_Sphere* other)
{
	float diff = (other->GetPosition() - GetPosition()).LengthSquared();
	float combinedRadius = length + other->GetLength();

	return (diff < combinedRadius * combinedRadius);
}

bool CCollider_Sphere::CheckAABB(CCollider_AABB* other)
{
	if (other->CheckPoint(GetPosition()))
		return true;

	Vector3 min, max;
	min = other->GetMin();
	max = other->GetMax();

	Vector3 closestPoint = other->GetClosestPoint(GetPosition());
	float diff = (closestPoint - GetPosition()).LengthSquared();

	return (diff < length * length);
}
