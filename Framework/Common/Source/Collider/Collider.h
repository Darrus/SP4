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
		AABB_2D
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

	inline void SetScale(Vector3 scale) { this->scale = scale; }
	inline Vector3 GetScale() const { return scale; }

	inline void SetOffset(Vector3 offset){ this->offset = offset; }
	inline Vector3 GetOffset() { return offset; }

	Vector3 GetMin();
	Vector3 GetMax();

protected:
	EntityBase* entity;
	Vector3 offset;
	Vector3 scale;
	COLLIDER_TYPE type;
};
