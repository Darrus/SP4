#include "CameraFollow.h"

// Utilities Include
#include "timer.h"
#include "MatrixStack.h"
#include "MouseController.h"
#include "KeyboardController.h"
#include "../Application.h"

CameraFollow::CameraFollow() :
dist(0.f), curDist(0.f), distSpeed(1.f),
rotSpeed(1.f),
curRotX(0.f), curRotZ(0.f),
rotX(0.f), rotZ(0.f),
mouseX(0.0), mouseY(0.0),
state(IDLE), ground(nullptr)
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

	mouseX = 0.f;
	mouseY = 0.f;
}

void CameraFollow::Update()
{
	float dt = (float)StopWatch::GetInstance()->GetDeltaTime();

	switch (state)
	{
	case IDLE:
		Control();
		break;
	}

	bool check = true;

	if (curDist < dist)
	{
		check = false;
		curDist += distSpeed * dt;
		if (curDist > dist)
			curDist = dist;
	}
	else if (curDist > dist)
	{
		check = false;
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
		check = false;
		curRotX += rotSpeed * dt;
		if (curRotX > rotX)
		{
			rotX = (int)rotX % 360;
			curRotX = rotX;
		}
	}
	else if (curRotX > rotX)
	{
		check = false;
		curRotX -= rotSpeed * dt;
		if (curRotX < rotX)
		{
			rotX = (int)rotX % 360;
			curRotX = rotX;
		}
	}
	mx.SetToRotation(curRotX, 1.f, 0.f, 0.f);
	front = mx * front;

	if (curRotZ < rotZ)
	{
		check = false;
		curRotZ += rotSpeed * dt;
		if (curRotZ > rotZ)
		{
			rotZ = (int)rotZ % 360;
			curRotZ = rotZ;
		}
	}
	else if (curRotZ > rotZ)
	{
		check = false;
		curRotZ -= rotSpeed * dt;
		if (curRotZ < rotZ)
		{
			rotZ = (int)rotZ % 360;
			curRotZ = rotZ;
		}
	}

	mx.SetToRotation(curRotZ, 0.f, 0.f, 1.f);
	front = mx * front;
	right = mx * right;

	position = target - front * curDist;
	HandleBoundary();
	up = right.Cross(front);

	if (check)
		state = IDLE;

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
		float diff = (float)(currMouseY - mouseY) * -1.f;
		
		rotX += diff * 0.1f;
		curRotX = rotX;
		mouseY = currMouseY;

		if (curRotX > 85.f)
		{
			curRotX = 85.f;
			rotX = 85.f;
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

		state = TRANSITION;
	}

	if (KeyboardController::GetInstance()->IsKeyPressed('Q'))
		rotZ += 90;
	else if (KeyboardController::GetInstance()->IsKeyPressed('E'))
		rotZ -= 90;

	double scroll = MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET);
	if (scroll != 0.0)
	{
		dist -= (float)scroll * 2.0f;
		if (dist < 10.f)
			dist = 10.f;
		else if (dist > 80.f)
			dist = 80.f;
		MouseController::GetInstance()->ResetMouseScroll();
	}
}

void CameraFollow::Transition(float rotX, float rotZ, float dist)
{
	SetRotX(rotX);
	SetRotZ(rotZ);
	SetDist(dist);
	state = TRANSITION;
}

void CameraFollow::HandleBoundary()
{
	if (!ground)
		return;

	Vector3 boundary = ground->GetScale() * 0.5f;

	if (position.x > boundary.x - 1.f)
		position.x = boundary.x - 1.f;
	else if (position.x < -boundary.x + 1.f)
		position.x = -boundary.x + 1.f;

	if (position.y > boundary.y - 1.f)
		position.y = boundary.y - 1.f;
	else if (position.y < -boundary.y + 1.f)
		position.y = -boundary.y + 1.f;
}