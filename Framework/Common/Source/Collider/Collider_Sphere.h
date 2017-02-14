#pragma once
#include "Collider.h"

class CCollider_AABB;

class CCollider_Sphere :
	public CCollider
{
private:
	float length;

public:
	CCollider_Sphere(EntityBase* entity = nullptr);
	virtual ~CCollider_Sphere();

	virtual void RenderCollider();
	virtual bool CheckCollision(CCollider* other);
	virtual bool CheckIntersection(Ray& ray);

	void SetLength(float _length);
	float GetLength() const;

private:
	bool CheckSphere(CCollider_Sphere* other);
	bool CheckAABB(CCollider_AABB* other);
};

