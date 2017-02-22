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

	void CalculateFrustrum();
	bool WithinFustrum(EntityBase* entity);

	void AddEntity(EntityBase* _newEntity, bool bAddToSpatialPartition = false);
	bool RemoveEntity(EntityBase* _existingEntity);
	bool MarkForDeletion(EntityBase* _existingEntity);
	void ClearEntityList();
	std::list<EntityBase*> *GetEntityList();

	inline void ShowCollider(const bool& show){ showCollider = show; }


private:
	std::list<EntityBase*> entityList;
	Vector3 frustrum[6];
	float d[6];
	bool showCollider;
};

#endif // ENTITY_MANAGER_H