#include "OverworldEntity.h"

// Graphics
#include "GraphicsManager.h"
#include "RenderHelper.h"

// Utilities includes
#include "KeyboardController.h"
#include "timer.h"

// Collider
#include "Collider\Collider_2DAABB.h"

OverworldEntity::OverworldEntity() :
moveSpeed(25.f), camera(nullptr)
{
	front.Set(0.f, 1.f, 0.f);
}


OverworldEntity::~OverworldEntity()
{
}

void OverworldEntity::Update()
{
	float dt = StopWatch::GetInstance()->GetDeltaTime();
	
	position += velocity;
	velocity.SetZero();
	
	camera->SetEntityPos(position);

	Mtx44 mx;
	mx.SetToRotation(camera->GetRotZ(), 0.f, 0.f, 1.f);
	Vector3 moveFront;
	moveFront = mx * front;
	right = moveFront.Cross(Vector3(0.f, 0.f, 1.f));

	if (KeyboardController::GetInstance()->IsKeyDown('W'))
		velocity += moveFront;
	else if (KeyboardController::GetInstance()->IsKeyDown('S'))
		velocity -= moveFront;
	if (KeyboardController::GetInstance()->IsKeyDown('D'))
		velocity += right;
	else if (KeyboardController::GetInstance()->IsKeyDown('A'))
		velocity -= right;

	if (velocity.LengthSquared() > 0)
		velocity = velocity.Normalized() * moveSpeed * dt;

	collider->SetOffset(velocity);

	Entity2D::Update();
}

void OverworldEntity::HandleCollision(EntityBase* entity)
{
	CCollider_2DAABB check;
	check.SetScale(collider->GetScale());

	check.SetOffset(Vector3(position.x + velocity.x, position.y, position.z));

	if (check.CheckCollision(entity->GetCollider()))
		velocity.x = 0.f;

	check.SetOffset(Vector3(position.x, position.y + velocity.y, position.z));
	if (check.CheckCollision(entity->GetCollider()))
		velocity.y = 0.f;
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