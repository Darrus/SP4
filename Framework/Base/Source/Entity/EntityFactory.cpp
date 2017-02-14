#include "EntityFactory.h"

#include "MeshBuilder.h"
#include "EntityManager.h"


EntityFactory::EntityFactory() :
manager(nullptr)
{
}


EntityFactory::~EntityFactory()
{
}

SpriteEntity* EntityFactory::CreateSprite(const string& meshName, SpriteEntity::SPRITE_RENDERMODE mode)
{
	SpriteEntity* result = new SpriteEntity(MeshBuilder::GetInstance()->GetMesh(meshName));
	result->SetTextRenderMode(mode);
	if (manager)
		manager->AddEntity(result);
	return result;
}

TextEntity* EntityFactory::CreateText(const string& text, const Color& _color, TextEntity::TEXT_RENDERMODE mode)
{
	TextEntity* result = new TextEntity(MeshBuilder::GetInstance()->GetMesh("text"), text, _color);
	result->SetTextRenderMode(mode);
	if (manager)
		manager->AddEntity(result);
	return result;
}
