#pragma once

#include "../Vector3.h"

class CCollider;

class Ray
{
private:
	Vector3 direction;
	Vector3 origin;
	float length;

public:
	Ray();
	~Ray();

	void SetDirection(Vector3 _direction);
	Vector3 GetDirection() const;

	void SetOrigin(Vector3 _origin);
	Vector3 GetOrigin() const;

	void SetLength(float _length);
	float GetLength() const;
};

