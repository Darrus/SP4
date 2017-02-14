#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include <string>

#include "SingletonTemplate.h"
#include "SpriteEntity.h"
#include "TextEntity.h"

using std::string;

class EntityManager;

class EntityFactory : public Singleton<EntityFactory>
{
private:
	friend Singleton<EntityFactory>;
	EntityManager* manager;

public:
	EntityFactory();
	~EntityFactory();

	inline void AttachEntityManager(EntityManager* manager){ this->manager = manager; }
	inline void DettachEntitymanager() { manager = nullptr; }
	inline EntityManager* GetEntityManager(){ return manager; }

	SpriteEntity* CreateSprite(const string& meshName, SpriteEntity::SPRITE_RENDERMODE mode);
	TextEntity* CreateText(const string& text, const Color& _color, TextEntity::TEXT_RENDERMODE mode);
};

#endif

