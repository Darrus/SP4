/******************************************************************************/
/*!
\file	Mtx44.h
\author Wen Sheng Tang
\par	email: tang_wen_sheng\@nyp.edu.sg
\brief
Matrix 4 by 4 use for affine transformation
*/
/******************************************************************************/
#ifndef MTX_44_H
#define MTX_44_H

#include "MyMath.h"
#include "Vector3.h"

#pragma warning( disable: 4290 ) //for throw(DivideByZero)

/******************************************************************************/
/*!
		Class Mtx44:
\brief	A 4 by 4 matrix
*/
/******************************************************************************/
class Mtx44
{
public:
	Mtx44(float a00 = 0, float a10 = 0, float a20 = 0, float a30 = 0, float a01 = 0, float a11 = 0, float a21 = 0, float a31 = 0, float a02 = 0, float a12 = 0, float a22 = 0, float a32 = 0, float a03 = 0, float a13 = 0, float a23 = 0, float a33 = 0);
	Mtx44(const float m[16]);
	Mtx44(const Mtx44 &rhs);
	void SetToIdentity(void);
	void Transpose(void);
	void SetToZero(void);
	Mtx44 GetTranspose() const;
	Mtx44 GetInverse() const throw( DivideByZero );
	Mtx44 operator*(const Mtx44& rhs) const;
	Mtx44 operator+(const Mtx44& rhs) const;
	Mtx44& operator=(const Mtx44& rhs);
	Mtx44 operator*(float scalar) const;
	Vector3 operator*(const Vector3& rhs) const;
	void SetToRotation(float degrees, float axisX, float axisY, float axisZ) throw( DivideByZero );
	void SetToScale(float sx, float sy, float sz);
	void SetToTranslation(float tx, float ty, float tz);
	void SetToFrustum(double left, double right, double	bottom, double top, double near, double far);
	void SetToLookAt(double eyeX, double eyeY, double eyeZ,
				double centerX, double centerY, double centerZ,
				double upX, double upY, double upZ);
	void SetToPerspective(double fovy, double aspect, double zNear, double zFar);
	void SetToOrtho(double left, double right, double bottom, double top, double nearVal, double farVal);

	float a[16];
};

#endif //MTX_44_H
