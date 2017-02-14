#include "EntityManager.h"
#include "EntityBase.h"
#include "Collider/Collider.h"
#include "../SceneGraph/SceneGraph.h"
#include "KeyboardController.h"

#include <iostream>
using namespace std;

// Update all entities
void EntityManager::Update(double _dt)
{
	if (KeyboardController::GetInstance()->IsKeyDown(VK_MENU) && KeyboardController::GetInstance()->IsKeyPressed('C'))
	{
		showCollider = !showCollider;
	}

	// Update all entities
	std::list<EntityBase*>::iterator it, end;
	end = entityList.end();
	for (it = entityList.begin(); it != end; ++it)
	{
		(*it)->Update(_dt);
	}

	// Render the Scene Graph
	CSceneGraph::GetInstance()->Update();

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
	// Render the Scene Graph
	CSceneGraph::GetInstance()->Render();
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

		// Remove from SceneNode too
		if (CSceneGraph::GetInstance()->DeleteNode(_existingEntity)==false)
		{
			cout << "EntityManager::RemoveEntity: Unable to remove this entity from Scene Graph" << endl;
		}

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