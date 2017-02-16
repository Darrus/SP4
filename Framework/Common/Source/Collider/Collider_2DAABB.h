#ifndef COLLIDER_2D_AABB_H
#define COLLIDER_2D_AABB_H

#include "Collider.h"
#include "../Vector3.h"

class CCollider_2DAABB : public CCollider
{
	float top, down, left, right;

public:
	CCollider_2DAABB();
	virtual ~CCollider_2DAABB();

	virtual void RenderCollider();
	virtual bool CheckCollision(CCollider* other);
	virtual bool CheckIntersection(Ray& ray);

	inline void SetScale(Vector3 scale){ this->scale = scale; }
	inline Vector3 GetScale(){ return this->scale; }

	Vector3 GetMin();
	Vector3 GetMax();

	inline float GetTop(){ return top; }
	inline float GetDown(){ return down; }
	inline float GetRight(){ return right; }
	inline float GetLeft(){ return left; }
};

#endif

