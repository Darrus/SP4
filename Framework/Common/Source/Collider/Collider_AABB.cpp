#include "Collider_AABB.h"
#include "Collider_Sphere.h"
#include "../EntityBase.h"
#include "../MeshBuilder.h"
#include "../RenderHelper.h"
#include "../GraphicsManager.h"
#include <GL/glew.h>

CCollider_AABB::CCollider_AABB(EntityBase* _entity) : 
	CCollider(_entity), rayFlag(false)
{
	type = AABB;
	scale.Set(1.f, 1.f, 1.f);
	offset.SetZero();
}


CCollider_AABB::~CCollider_AABB()
{

}

bool CCollider_AABB::CheckCollision(CCollider* other)
{
	switch (other->GetType())
	{
	case AABB:
		return CheckAABB((CCollider_AABB*)other);
		break;
	case SPHERE:
		return CheckSphere((CCollider_Sphere*)other);
		break;
	}

	return false;
}

Vector3 CCollider_AABB::GetClosestPoint(Vector3 point)
{
	Vector3 closestPoint;
	Vector3 min = GetMin();
	Vector3 max = GetMax();

	closestPoint.x = (point.x < min.x) ? min.x : (point.x > max.x) ? max.x : point.x;
	closestPoint.y = (point.y < min.y) ? min.y : (point.y > max.y) ? max.y : point.y;
	closestPoint.z = (point.z < min.z) ? min.z : (point.z > max.z) ? max.z : point.z;

	return closestPoint;
}

bool CCollider_AABB::CheckPoint(Vector3 point)
{
	Vector3 min = GetMin();
	Vector3 max = GetMax();

	return (point.x > min.x && point.x < max.x &&
		point.y > min.y && point.y < max.y &&
		point.z > min.z && point.z < max.z);
}

bool CCollider_AABB::CheckIntersection(Ray& ray)
{
	float tmin, tmax, tymin, tymax, tzmin, tzmax;
	Vector3 min = GetMin();
	Vector3 max = GetMax();

	if (ray.GetDirection().x >= 0)
	{
		tmin = (min.x - ray.GetOrigin().x) / ray.GetDirection().x;
		tmax = (max.x - ray.GetOrigin().x) / ray.GetDirection().x;
	}
	else
	{
		tmin = (max.x - ray.GetOrigin().x) / ray.GetDirection().x;
		tmax = (min.x - ray.GetOrigin().x) / ray.GetDirection().x;
	}

	if (ray.GetDirection().y >= 0)
	{
		tymin = (min.y - ray.GetOrigin().y) / ray.GetDirection().y;
		tymax = (max.y - ray.GetOrigin().y) / ray.GetDirection().y;
	}
	else
	{
		tymin = (max.y - ray.GetOrigin().y) / ray.GetDirection().y;
		tymax = (min.y - ray.GetOrigin().y) / ray.GetDirection().y;
	}

	if ((tmin > tymax) || (tymin > tmax))
		return false;

	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;

	if (ray.GetDirection().z >= 0)
	{
		tzmin = (min.z - ray.GetOrigin().z) / ray.GetDirection().z;
		tzmax = (max.z - ray.GetOrigin().z) / ray.GetDirection().z;
	}
	else
	{
		tzmin = (max.z - ray.GetOrigin().z) / ray.GetDirection().z;
		tzmax = (min.z - ray.GetOrigin().z) / ray.GetDirection().z;
	}

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	if (tzmin > tmin)
		tmin = tzmin;
	
	if (tzmax < tmax)
		tmax = tzmax;

	return true;
}

bool CCollider_AABB::CheckAABB(CCollider_AABB* other)
{
	Vector3 thisMin = GetMin();
	Vector3 thisMax = GetMax();

	Vector3 otherMin = other->GetMin();
	Vector3 otherMax = other->GetMax();

	if (thisMin.x < otherMax.x && thisMax.x > otherMin.x &&
		thisMin.y < otherMax.y && thisMax.y > otherMin.y &&
		thisMin.z < otherMax.z && thisMax.z > otherMin.z)
		return true;
	else if (rayFlag)
	{
		Vector3 direction = entity->GetPosition() - entity->lastPosition;
		Ray ray;
		
		ray.SetOrigin(entity->lastPosition);
		ray.SetDirection(direction.Normalized());
		ray.SetLength(direction.Length());

		return CheckIntersection(ray);
	}
	else
		return false;
}

bool CCollider_AABB::CheckSphere(CCollider_Sphere* other)
{
	if (CheckPoint(other->GetPosition()))
		return true;

	Vector3 min = GetMin();
	Vector3 max = GetMax();

	Vector3 closestPoint = GetClosestPoint(other->GetPosition());
	float diff = (closestPoint - other->GetPosition()).LengthSquared();

	return (diff < other->GetLength() * other->GetLength());
}

void CCollider_AABB::SetRayFlag(bool flag)
{
	rayFlag = flag;
}

void CCollider_AABB::RenderCollider()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(entity->GetPosition().x + offset.x, entity->GetPosition().y + offset.y, entity->GetPosition().z + offset.z);
	modelStack.Scale(scale.x, scale.y, scale.z);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("cube"));
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	modelStack.PopMatrix();
}

Vector3 CCollider_AABB::GetMin()
{
	GetPosition();
	
	return Vector3((position.x + offset.x) - scale.x * 0.5f,
				   (position.y + offset.y) - scale.y * 0.5f,
				   (position.z + offset.z) - scale.z * 0.5f);
}

Vector3 CCollider_AABB::GetMax()
{
	GetPosition();
	
	return Vector3((position.x + offset.x) + scale.x * 0.5f,
				   (position.y + offset.y) + scale.y * 0.5f,
				   (position.z + offset.z) + scale.z * 0.5f);
}

void CCollider_AABB::SetScale(Vector3 _scale)
{
	this->scale = _scale;
}

Vector3 CCollider_AABB::GetScale()
{
	return scale;
}

void CCollider_AABB::SetOffset(Vector3 _offset)
{
	offset = _offset;
}

Vector3 CCollider_AABB::GetOffset()
{
	return offset;
}