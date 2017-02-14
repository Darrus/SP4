#ifndef ENTITY_BASE_H
#define ENTITY_BASE_H

#include "Vector3.h"
#include "Collider\Collider.h"
#include "Mesh.h"

class EntityBase
{
public:
	EntityBase();
	virtual ~EntityBase();

	virtual void Update();
	virtual void Render();
	virtual void RenderUI();
	virtual void HandleCollision(EntityBase* entity);

	inline void SetPosition(const Vector3& _value){ position = _value; lastPosition = _value; };
	inline Vector3 GetPosition(){ return position; };

	inline void SetScale(const Vector3& _value){ scale = _value; };
	inline Vector3 GetScale(){ return scale; };

	bool IsDone();
	void SetIsDone(const bool _value);

	void SetMesh(Mesh* mesh);
	void SetRenderFlag(bool flag);
	bool GetRenderFlag();

	// Check if this entity has a collider class parent
	virtual bool HasCollider(void) const;
	// Set the collider
	virtual void SetCollider(CCollider* collider);
	// Set Collider flag
	void SetColliderFlag(bool flag);
	// Returns the current collider
	virtual CCollider* GetCollider();
	// Remove Collider
	virtual void RemoveCollider();


	Vector3 lastPosition;

protected:
	Vector3 position;
	Vector3 scale;

	CCollider* collider;

	bool isDone;
	bool m_bCollider;
	bool bRender;
};

#endif // ENTITY_BASE_H