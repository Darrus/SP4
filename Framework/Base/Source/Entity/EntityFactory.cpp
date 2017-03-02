#include "EntityFactory.h"

#include "MeshBuilder.h"
#include "EntityManager.h"

#include "Collider\Collider_2DAABB.h"


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

AssetEntity* EntityFactory::CreateAsset(const string& meshName, Vector3 position, Vector3 scale, bool collider)
{
	AssetEntity* result = new AssetEntity(meshName);
	result->SetPosition(position);
	result->SetScale(scale);
	if (collider)
		result->SetCollider(new CCollider_2DAABB());
	if (manager)
		manager->AddEntity(result);
	return result;
}

NPC* EntityFactory::CreateMoogle(Vector3 position, string dialogue)
{
	NPC* npc = new NPC();
	npc->GetAnimator()->AddAnimation("npc_walk_front");
	npc->GetAnimator()->AddAnimation("npc_walk_back");
	npc->GetAnimator()->AddAnimation("npc_walk_right");
	npc->GetAnimator()->AddAnimation("npc_walk_left");
	npc->GetAnimator()->PlayAnimation("npc_walk_front");
	npc->SetScale(Vector3(5.f, 7.f, 1.f));
	npc->SetPosition(position);
	npc->LoadDialogue(dialogue);
	npc->SetCollider(new CCollider_2DAABB());
	npc->SetMoveSpeed(20.f);
	return npc;
}