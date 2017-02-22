#include "OverworldEntity.h"

// Graphics
#include "GraphicsManager.h"
#include "RenderHelper.h"

// Utilities includes
#include "KeyboardController.h"
#include "timer.h"
#include "Vector3.h"

// Collider
#include "Collider\Collider_2DAABB.h"

OverworldEntity::OverworldEntity() :
camera(nullptr)
{
}


OverworldEntity::~OverworldEntity()
{
}

void OverworldEntity::Update()
{
	Entity2D::Update();
}

void OverworldEntity::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Rotate(camera->GetRotZ(), 0.f, 0.f, 1.f);
	modelStack.Translate(0.f, -scale.y * 0.5f, 0.f);
	modelStack.Rotate(camera->GetRotX(), 1.f, 0.f, 0.f);
	modelStack.Translate(0.f, scale.y * 0.5f, 0.f);
	modelStack.Scale(scale.x, scale.y, scale.z);
	anim.Render();
	modelStack.PopMatrix();
}