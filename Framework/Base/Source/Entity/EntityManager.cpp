#include "EntityManager.h"
#include "EntityBase.h"
#include "Collider/Collider.h"
#include "KeyboardController.h"

// Graphics
#include "GraphicsManager.h"

#include <iostream>
using namespace std;

// Update all entities
void EntityManager::Update()
{
	if (KeyboardController::GetInstance()->IsKeyDown(VK_MENU) && KeyboardController::GetInstance()->IsKeyPressed('C'))
	{
		showCollider = !showCollider;
	}

	// Update all entities
	std::list<EntityBase*>::iterator it, it2, end;
	end = entityList.end();
	for (it = entityList.begin(); it != end; ++it)
	{
		(*it)->Update();
	}

	// Clean up entities that are done
	it = entityList.begin();
	while (it != end)
	{
		if ((*it)->IsDone())
		{
			// Delete if done
			delete *it;
			it = entityList.erase(it);
		}
		else
		{
			// Move on otherwise
			++it;
		}
	}
}

// Render all entities
void EntityManager::Render()
{
	CalculateFrustrum();

	std::list<EntityBase*>::iterator it, end;
	end = entityList.end();
	for (it = entityList.begin(); it != end; ++it)
	{
		if ((*it)->GetRenderFlag() && WithinFustrum(*it))
		{
			(*it)->Render();
			if (showCollider && (*it)->HasCollider())
				(*it)->GetCollider()->RenderCollider();
		}
	}
}
// Render the UI entities
void EntityManager::RenderUI()
{
	// Render all entities UI
	std::list<EntityBase*>::iterator it, end;
	end = entityList.end();
	for (it = entityList.begin(); it != end; ++it)
	{
		if ((*it)->GetRenderFlag())
			(*it)->RenderUI();
	}
}

// Add an entity to this EntityManager
void EntityManager::AddEntity(EntityBase* _newEntity, bool bAddToSpatialPartition)
{
	entityList.push_back(_newEntity);
}

// Remove an entity from this EntityManager
bool EntityManager::RemoveEntity(EntityBase* _existingEntity)
{
	// Find the entity's iterator
	std::list<EntityBase*>::iterator findIter = std::find(entityList.begin(), entityList.end(), _existingEntity);

	// Delete the entity if found
	if (findIter != entityList.end())
	{
		delete *findIter;
		findIter = entityList.erase(findIter);
		return true;	
	}
	// Return false if not found
	return false;
}

// Mark an entity for deletion
bool EntityManager::MarkForDeletion(EntityBase* _existingEntity)
{
	// Find the entity's iterator
	std::list<EntityBase*>::iterator findIter = std::find(entityList.begin(), entityList.end(), _existingEntity);

	// Delete the entity if found
	if (findIter != entityList.end())
	{
		(*findIter)->SetIsDone(true);
		return true;
	}
	// Return false if not found
	return false;
}

void EntityManager::ClearEntityList()
{
	std::list<EntityBase*>::iterator it = entityList.begin();
	while (it != entityList.end())
	{
		delete *it;
		it = entityList.erase(it);
	}
}

// Constructor
EntityManager::EntityManager() : 
showCollider(false)
{
}

// Destructor
EntityManager::~EntityManager()
{
}

std::list<EntityBase*> *EntityManager::GetEntityList()
{
	return &entityList;
}

void EntityManager::CalculateFrustrum()
{
	float t;

	Mtx44 MVP;
	MVP = GraphicsManager::GetInstance()->GetProjectionMatrix() * GraphicsManager::GetInstance()->GetViewMatrix();

	// Right Plane
	frustrum[0].x = MVP.a[3] - MVP.a[0];
	frustrum[0].y = MVP.a[7] - MVP.a[4];
	frustrum[0].z = MVP.a[11] - MVP.a[8];
	d[0] = MVP.a[15] - MVP.a[12];

	t = frustrum[0].Length();
	frustrum[0].x /= t;
	frustrum[0].y /= t;
	frustrum[0].z /= t;
	d[0] /= t;

	// Left Plane
	frustrum[1].x = MVP.a[3] + MVP.a[0];
	frustrum[1].y = MVP.a[7] + MVP.a[4];
	frustrum[1].z = MVP.a[11] + MVP.a[8];
	d[1] = MVP.a[15] + MVP.a[12];

	t = frustrum[1].Length();
	frustrum[1].x /= t;
	frustrum[1].y /= t;
	frustrum[1].z /= t;
	d[1] /= t;

	// Bottom Plane
	frustrum[2].x = MVP.a[3] + MVP.a[1];
	frustrum[2].y = MVP.a[7] + MVP.a[5];
	frustrum[2].z = MVP.a[11] + MVP.a[9];
	d[2] = MVP.a[15] + MVP.a[13];

	t = frustrum[2].Length();
	frustrum[2].x /= t;
	frustrum[2].y /= t;
	frustrum[2].z /= t;
	d[2] /= t;

	// Top Plane
	frustrum[3].x = MVP.a[3] - MVP.a[1];
	frustrum[3].y = MVP.a[7] - MVP.a[5];
	frustrum[3].z = MVP.a[11] - MVP.a[9];
	d[3] = MVP.a[15] - MVP.a[13];

	t = frustrum[3].Length();
	frustrum[3].x /= t;
	frustrum[3].y /= t;
	frustrum[3].z /= t;
	d[3] /= t;

	// Far Plane
	frustrum[4].x = MVP.a[3] - MVP.a[2];
	frustrum[4].y = MVP.a[7] - MVP.a[6];
	frustrum[4].z = MVP.a[11] - MVP.a[10];
	d[4] = MVP.a[15] - MVP.a[14];

	t = frustrum[4].Length();
	frustrum[4].x /= t;
	frustrum[4].y /= t;
	frustrum[4].z /= t;
	d[4] /= t;

	// Near Plane
	frustrum[5].x = MVP.a[3] + MVP.a[2];
	frustrum[5].y = MVP.a[7] + MVP.a[6];
	frustrum[5].z = MVP.a[11] + MVP.a[10];
	d[5] = MVP.a[15] + MVP.a[14];

	t = frustrum[5].Length();
	frustrum[5].x /= t;
	frustrum[5].y /= t;
	frustrum[5].z /= t;
	d[5] /= t;
}

bool EntityManager::WithinFustrum(EntityBase* entity)
{
	Vector3 max = entity->GetPosition() + entity->GetScale() * 0.5f;
	Vector3 min = entity->GetPosition() - entity->GetScale() * 0.5f;

	for (int i = 0; i < 6; ++i)
	{
		if ((frustrum[i].x * max.x + frustrum[i].y * max.y + frustrum[i].z * max.z + d[i] <= 0) &&
			(frustrum[i].x * min.x + frustrum[i].y * min.y + frustrum[i].z * min.z + d[i] <= 0))
		{
			return false;
		}
	}

	return true;
}