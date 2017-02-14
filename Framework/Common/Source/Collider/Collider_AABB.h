#pragma once
#include "Collider.h"

class CCollider_Sphere;

class CCollider_AABB : public CCollider
{
private:
	bool rayFlag;
	Vector3 scale;
	Vector3 offset;

public:
	CCollider_AABB(EntityBase* _entity = nullptr);
	virtual ~CCollider_AABB();

	virtual bool CheckCollision(CCollider* other);
	virtual bool CheckIntersection(Ray& ray);
	virtual void RenderCollider();

	bool CheckPoint(Vector3 point);
	Vector3 GetClosestPoint(Vector3 point);

	void SetScale(Vector3 _scale);
	Vector3 GetScale();

	void SetOffset(Vector3 _offset);
	Vector3 GetOffset();

	void SetRayFlag(bool flag);

	Vector3 GetMin();
	Vector3 GetMax();

private:
	bool CheckAABB(CCollider_AABB* other);
	bool CheckSphere(CCollider_Sphere* other);
};