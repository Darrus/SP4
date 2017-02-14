#include "Collider.h"
#include "../EntityBase.h"

CCollider::CCollider(EntityBase* _entity) :
entity(_entity), type(NIL)
{
	offset.SetZero();
}


CCollider::~CCollider()
{
}


void CCollider::SetEntity(EntityBase* _entity)
{
	this->entity = _entity;
}

EntityBase* CCollider::GetEntity() const
{
	return entity;
}

void CCollider::SetPosition(Vector3 _position)
{
	offset = _position;
}

Vector3 CCollider::GetPosition()
{
	if (entity)
		offset = entity->GetPosition();
	return offset;
}

CCollider::COLLIDER_TYPE CCollider::GetType() const
{
	return type;
}
