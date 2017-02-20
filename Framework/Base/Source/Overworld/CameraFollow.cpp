#include "CameraFollow.h"

// Utilities Include
#include "timer.h"
#include "MatrixStack.h"
#include "MouseController.h"
#include "../Application.h"

CameraFollow::CameraFollow() :
dist(0.f), curDist(0.f), distSpeed(1.f),
rotSpeed(1.f),
curRotX(0.f), curRotZ(0.f),
rotX(0.f), rotZ(0.f),
mouseX(0.0), mouseY(0.0),
state(IDLE)
{
}


CameraFollow::~CameraFollow()
{
}

void CameraFollow::Init(float dist, float followSpeed)
{
	this->dist = dist;
	curDist = dist;
	this->followSpeed = followSpeed;
	
	defaultTarget = Vector3(0.f, 0.f, 0.f);
	target = defaultTarget;

	defaultPosition = Vector3(0.f, 0.f, 1.f);
	position = target + Vector3(0.f, 0.f, 1.f) * dist;

	defaultUp = Vector3(0.f, 1.f, 0.f);
	up = Vector3(1.f, 0.f, 0.f).Cross(target - position);
}

void CameraFollow::Update()
{
	float dt = (float)StopWatch::GetInstance()->GetDeltaTime();
	state = IDLE;
	Control();

	if (curDist < dist)
	{
		state = TRANSITION;
		curDist += distSpeed * dt;
		if (curDist > dist)
			curDist = dist;
	}
	else if (curDist > dist)
	{
		state = TRANSITION;
		curDist -= distSpeed * dt;
		if (curDist < dist)
			curDist = dist;
	}

	target.Lerp(entityPos, followSpeed, dt);
	Vector3 front = Vector3(0.f, 0.f, -1.f);
	Vector3 right = Vector3(1.f, 0.f, 0.f);

	Mtx44 mx;
	if (curRotX < rotX)
	{
		state = TRANSITION;
		curRotX += rotSpeed * dt;
		if (curRotX > rotX)
			curRotX = rotX;
	}
	else if (curRotX > rotX)
	{
		state = TRANSITION;
		curRotX -= rotSpeed * dt;
		if (curRotX < rotX)
			curRotX = rotX;
	}
	mx.SetToRotation(curRotX, 1.f, 0.f, 0.f);
	front = mx * front;

	if (curRotZ < rotZ)
	{
		state = TRANSITION;
		curRotZ += rotSpeed * dt;
		if (curRotZ > rotZ)
			curRotZ = rotZ;
	}
	else if (curRotZ > rotZ)
	{
		state = TRANSITION;
		curRotZ -= rotSpeed * dt;
		if (curRotZ < rotZ)
			curRotZ = rotZ;
	}

	mx.SetToRotation(curRotZ, 0.f, 0.f, 1.f);
	front = mx * front;
	right = mx * right;

	position = target - front * curDist;
	up = right.Cross(front);
}

void CameraFollow::Control()
{
	if (MouseController::GetInstance()->IsButtonPressed(1))
	{
		MouseController::GetInstance()->GetMousePosition(mouseX, mouseY);
	}

	if (MouseController::GetInstance()->IsButtonDown(1))
	{
		double currMouseX, currMouseY;
		MouseController::GetInstance()->GetMousePosition(currMouseX, currMouseY);

		float diff = (float)(currMouseY - mouseY);
		rotX += diff * 0.01f;
		curRotX += diff * 0.01f;

		if (curRotX > 70.f)
		{
			curRotX = 70.f;
			rotX = 70.f;
		}
		else if (curRotX < 0.f)
		{
			curRotX = 0.f;
			rotX = 0.f;
		}
	}

	if (MouseController::GetInstance()->IsButtonPressed(0))
	{
		double currMouseX, currMouseY;
		MouseController::GetInstance()->GetMousePosition(currMouseX, currMouseY);
		float windowWidth = Application::GetInstance().GetWindowWidth();
		if (currMouseX > windowWidth * 0.5f)
			rotZ -= 90;
		else
			rotZ += 90;
	}
}

void CameraFollow::Transition(float rotX, float rotZ, float dist)
{
	SetRotX(rotX);
	SetRotZ(rotZ);
	SetDist(dist);
	state = TRANSITION;
}