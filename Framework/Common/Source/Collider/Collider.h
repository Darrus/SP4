#pragma once
#include "../Vector3.h"
#include "../Ray/Ray.h"

class EntityBase;

class CCollider
{
public:
	enum COLLIDER_TYPE
	{
		NIL,
		AABB,
		SPHERE
	};

	CCollider(EntityBase* _entity = nullptr);
	virtual ~CCollider();

	virtual void RenderCollider() = 0;
	virtual bool CheckCollision(CCollider* other) = 0;
	virtual bool CheckIntersection(Ray& ray) = 0;

	void SetEntity(EntityBase* _entity);
	EntityBase* GetEntity() const;
	COLLIDER_TYPE GetType() const;

	void SetPosition(Vector3 _position);
	Vector3 GetPosition();

protected:
	EntityBase* entity;
	Vector3 position;
	COLLIDER_TYPE type;
};
