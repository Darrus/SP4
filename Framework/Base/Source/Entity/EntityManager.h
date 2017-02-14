#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "SingletonTemplate.h"
#include <list>
#include "Vector3.h"

class EntityBase;

class EntityManager
{
public:
	EntityManager();
	virtual ~EntityManager();

	void Update();
	void Render();
	void RenderUI();

	void AddEntity(EntityBase* _newEntity, bool bAddToSpatialPartition = false);
	bool RemoveEntity(EntityBase* _existingEntity);
	bool MarkForDeletion(EntityBase* _existingEntity);
	void ClearEntityList();
	std::list<EntityBase*> *GetEntityList();

	inline void ShowCollider(const bool& show){ showCollider = show; }

private:
	std::list<EntityBase*> entityList;
	bool showCollider;
};

#endif // ENTITY_MANAGER_H