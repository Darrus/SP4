#include "OverworldEntity.h"

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
	
	Entity2D::Update();
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
}

void OverworldEntity::HandleCollision(EntityBase* entity)
{
	CCollider_2DAABB* check = (CCollider_2DAABB*)collider;
	if (check->GetTop() > 0.f || check->GetDown() > 0.f)
		velocity.y = 0.f;
	if (check->GetLeft() > 0.f || check->GetRight() > 0.f)
		velocity.x = 0.f;
}