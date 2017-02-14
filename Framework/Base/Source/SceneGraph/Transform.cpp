#include "Transform.h"
#include <iostream>

using namespace std;

// Default Constructor
CTransform::CTransform(void)
{
	Mtx.SetToIdentity();
	DefaultMtx.SetToIdentity();
}

// Overloaded Constructor
CTransform::CTransform(const float dx, const float dy, const float dz)
{
	Mtx.SetToTranslation(dx, dy, dz);
}

// Destructor
CTransform::~CTransform(void)
{

}

void CTransform::SetIdentity()
{
	Mtx.SetToIdentity();
}

// Apply a translation to the Transformation Matrix
void CTransform::ApplyTranslate(const float dx, const float dy, const float dz)
{
	Mtx44 TempMtx;
	TempMtx.SetToTranslation(dx, dy, dz);
	Mtx = Mtx*TempMtx;
}

void CTransform::ApplyScale(const float dx, const float dy, const float dz)
{
	Mtx44 TempMtx;
	TempMtx.SetToScale(dx, dy, dz);
	Mtx = Mtx * TempMtx;
}

// Get the translation from the Transformation Matrix
void CTransform::GetTranslate(float& x, float& y, float& z)
{
	x = Mtx.a[12];
	y = Mtx.a[13];
	z = Mtx.a[14];
}
// Apply a rotation to the Transformation Matrix
void CTransform::ApplyRotate(const float angle, const float rx, const float ry, const float rz)
{
	Mtx44 TempMtx;
	TempMtx.SetToRotation(angle, rx, ry, rz);
	Mtx = Mtx*TempMtx;
}
// Get the rotation from the Transformation Matrix
float CTransform::GetRotate(const AXIS theAxis)
{
	if (theAxis == X_AXIS)
	{
		float y = acos(Mtx.a[5]);	// Equals to cos a
		float z = asin(-Mtx.a[9]);	// Equals to sin a

		if (abs(y - z) < Math::EPSILON)
			return y;
		else
		{
			// This Matrix is wrong!
		}
	}
	else if (theAxis == Y_AXIS)
	{
		float x = acos(Mtx.a[0]);	// Equals to cos a
		float z = asin(Mtx.a[8]);	// Equals to -sin a
		if (abs(x - z) < Math::EPSILON)
			return x;
		else
		{
			// This Matrix is wrong!
		}
	}
	else // Z_AXIS
	{
		float x = acos(Mtx.a[0]);	// Equals to cos a
		float y = asin(-Mtx.a[4]);	// Equals to -sin a
		if (abs(x - y) < Math::EPSILON)
			return x;
		else
		{
			// This Matrix is wrong!
		}
	}
	return 0.0f;
}
// Set the scale of the Transformation Matrix
void CTransform::SetScale(const float sx, const float sy, const float sz)
{
	float scaleX = sx, scaleY = sy, scaleZ = sz;
	if (scaleX == 0.0f)
		scaleX = 1.0f;
	if (scaleY == 0.0f)
		scaleY = 1.0f;
	if (scaleZ == 0.0f)
		scaleZ = 1.0f;

	Mtx.SetToScale(scaleX, scaleY, scaleZ);
}
// Get the scale from the Transformation Matrix
void CTransform::GetScale(float& x, float& y, float& z)
{
	x = Mtx.a[0];
	y = Mtx.a[5];
	z = Mtx.a[10];
}

// Apply a Transformation Matrix to the Transformation Matrix here
void CTransform::ApplyTransform(Mtx44 newMTX)
{
	Mtx = Mtx * newMTX;
}

// Reset the transformation matrix to identity matrix
void CTransform::Reset(void)
{
	Mtx.SetToIdentity();
}

// Get the transformation matrix
Mtx44* CTransform::GetTransform(void)
{
	return &Mtx;
}

// Print Self
void CTransform::PrintSelf(void) const
{
	cout << "======================================================================" << endl;
	cout << "CTransform::PrintSelf" << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "[\t" << Mtx.a[ 0] << "\t" << Mtx.a[ 4] << "\t" << Mtx.a[ 8] << "\t" << Mtx.a[12] << "\t]" << endl;
	cout << "[\t" << Mtx.a[ 1] << "\t" << Mtx.a[ 5] << "\t" << Mtx.a[ 9] << "\t" << Mtx.a[13] << "\t]" << endl;
	cout << "[\t" << Mtx.a[ 2] << "\t" << Mtx.a[ 6] << "\t" << Mtx.a[10] << "\t" << Mtx.a[14] << "\t]" << endl;
	cout << "[\t" << Mtx.a[ 3] << "\t" << Mtx.a[ 7] << "\t" << Mtx.a[11] << "\t" << Mtx.a[15] << "\t]" << endl;
	cout << "======================================================================" << endl;
}
