#include "Ray.h"


Ray::Ray()
{
}

Ray::~Ray()
{
}

void Ray::SetDirection(Vector3 _direction)
{
	direction = _direction;
}

Vector3 Ray::GetDirection() const
{
	return direction;
}

void Ray::SetOrigin(Vector3 _origin)
{
	origin = _origin;
}

Vector3 Ray::GetOrigin() const
{
	return origin;
}

void Ray::SetLength(float _length)
{
	length = _length;
}

float Ray::GetLength() const
{
	return length;
}
