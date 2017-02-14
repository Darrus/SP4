#include "EntityManager.h"
#include "EntityBase.h"
#include "Collider/Collider.h"
#include "KeyboardController.h"

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

	// Collision Check
	end = entityList.end();
	for (it = entityList.begin(); it != end; ++it)
	{
		if (!(*it)->HasCollider())
			continue;

		for (it2 = std::next(it); it2 != end; ++it2)
		{
			if (!(*it2)->HasCollider())
				continue;

			if ((*it)->GetCollider()->CheckCollision((*it2)->GetCollider()))
			{
				(*it)->HandleCollision(*it2);
				(*it2)->HandleCollision(*it);
			}
		}
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
	std::list<EntityBase*>::iterator it, end;
	end = entityList.end();
	for (it = entityList.begin(); it != end; ++it)
	{
		if ((*it)->GetRenderFlag())
			(*it)->Render();
	}

	if (showCollider)
	{
		std::list<EntityBase*>::iterator it, end;
		end = entityList.end();
		for (it = entityList.begin(); it != end; ++it)
		{
			if ((*it)->HasCollider())
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