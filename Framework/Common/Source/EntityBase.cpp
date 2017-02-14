#include "EntityBase.h"

EntityBase::EntityBase() 
	: position(0.0f, 0.0f, 0.0f)
	, scale(1.0f, 1.0f, 1.0f)
	, isDone(false)
	, m_bCollider(false)
	, collider(nullptr)
	, bRender(true)
{
}

EntityBase::~EntityBase()
{
	if (collider)
		delete collider;
	collider = nullptr;
}

void EntityBase::Update(double _dt)
{
}

void EntityBase::Render()
{
}

void EntityBase::RenderUI()
{
}

bool EntityBase::IsDone()
{
	return isDone;
}

void EntityBase::SetIsDone(bool _value)
{
	isDone = _value;
}

// Check if this entity has a collider class parent
bool EntityBase::HasCollider(void) const
{
	return m_bCollider;
}

// Set the flag to indicate if this entity has a collider class parent
void EntityBase::SetCollider(CCollider* collider)
{
	m_bCollider = true;
	this->collider = collider;
}

// Set Collider flag
void EntityBase::SetColliderFlag(bool flag)
{
	m_bCollider = flag;
}

// Returns the current collider
CCollider* EntityBase::GetCollider()
{
	return collider;
}

// Removes current collider
void EntityBase::RemoveCollider()
{
	delete collider;
	collider = nullptr;
	m_bCollider = false;
}

void EntityBase::HandleCollision(EntityBase* entity)
{
	SetIsDone(true);
}

void EntityBase::SetRenderFlag(bool flag)
{
	bRender = flag;
}

bool EntityBase::GetRenderFlag()
{
	return bRender;
}