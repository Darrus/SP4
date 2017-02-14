#include "Entity2D.h"
#include "GraphicsManager.h"

Entity2D::Entity2D()
{
	position.Set(400.f, 300.f, 10.f);
	scale.Set(50.f, 50.f, 1.f);
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