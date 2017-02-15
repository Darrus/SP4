#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

Mtx44 Camera::GetViewMatrix()
{
	Mtx44 result;
	result.SetToLookAt(position.x, position.y, position.z,
		target.x, target.y, target.z,
		up.x, up.y, up.z);
	return result;
}

void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
}

void Camera::Update(double dt)
{

}

Vector3 Camera::GetCameraPos() const
{
	return position;
}

void Camera::SetCameraPos(Vector3 pos)
{
	position = pos;
}
Vector3 Camera::GetCameraTarget() const
{
	return target;
}
void Camera::SetCameraTarget(Vector3 target)
{
	this->target = target;
}
Vector3 Camera::GetCameraUp() const
{
	return up;
}
void Camera::SetCameraUp(Vector3 up)
{
	this->up = up;
}

void Camera::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}