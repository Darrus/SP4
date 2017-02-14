#include "Entity2D.h"
#include "GraphicsManager.h"

#include "KeyboardController.h"

Entity2D::Entity2D()
{
	position.Set(0.f, 0.f, 1.f);
	scale.Set(1.f, 1.f, 1.f);
	bRender = true;
}


Entity2D::~Entity2D()
{
}

void Entity2D::Update()
{
	anim.Update();
}

void Entity2D::Render()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);
	anim.Render();
	modelStack.PopMatrix();
}

void Entity2D::RenderUI()
{

}

void Entity2D::HandleCollision(EntityBase* entity)
{
}