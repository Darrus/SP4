/******************************************************************************/
/*!
\file	Mtx44.cpp
\author Wen Sheng Tang
\par	email: tang_wen_sheng\@nyp.edu.sg
\brief
Matrix 4 by 4 use for affine transformation
*/
/******************************************************************************/
#include "Mtx44.h"
/******************************************************************************/
/*!
\brief
Default Constructor. Default values are zero

\param a00 to a33 - Initial values for the matrix in (row, column) format

\exception None
\return None
*/
/******************************************************************************/
Mtx44::Mtx44(float a00, float a10, float a20, float a30, float a01, float a11, float a21, float a31, float a02, float a12, float a22, float a32, float a03, float a13, float a23, float a33) {
	a[0] = a00;
	a[1] = a10;
	a[2] = a20;
	a[3] = a30;
	a[4] = a01;
	a[5] = a11;
	a[6] = a21;
	a[7] = a31;
	a[8] = a02;
	a[9] = a12;
	a[10] = a22;
	a[11] = a32;
	a[12] = a03;
	a[13] = a13;
	a[14] = a23;
	a[15] = a33;
}

/******************************************************************************/
/*!
\brief
Constructor with array of 16 floats. Default values are zero

\param m[16] - Initial values for the matrix in column major format

\exception None
\return None
*/
/******************************************************************************/
Mtx44::Mtx44(const float m[16]) {
	for(int i = 0; i < 16; i++)
		a[i] = m[i];
}

/******************************************************************************/
/*!
\brief
Copy constructor
*/
/******************************************************************************/
Mtx44::Mtx44(const Mtx44 &rhs) {
	for(int i = 0; i < 16; i++)
		a[i] = rhs.a[i];
}

/******************************************************************************/
/*!
\brief
Set the matrix to an identity matrix (1's along the diagonal)
*/
/******************************************************************************/
void Mtx44::SetToIdentity(void) {
	SetToZero();
	a[0] = a[5] = a[10] = a[15] = 1;
}

/******************************************************************************/
/*!
\brief
Helper function swap
*/
/******************************************************************************/
void swap(float &v1, float &v2) {
	float temp = v1;
	v1 = v2;
	v2 = temp;
}

/******************************************************************************/
/*!
\brief
Set this matrix to its Transpose
*/
/******************************************************************************/
void Mtx44::Transpose(void) {
	for(int i = 0; i < 4; i++)
		for(int j = i + 1; j < 4; j++)
			swap(a[i * 4 + j], a[j * 4 + i]);
}

/******************************************************************************/
/*!
\brief
Set this matrix to zero
*/
/******************************************************************************/
void Mtx44::SetToZero(void) {
	for(int i = 0; i < 16; i++)
		a[i] = 0;
}

/******************************************************************************/
/*!
\brief
Return a new matrix that is a transpose of this matrix

\return 
A new matrix
*/
/******************************************************************************/
Mtx44 Mtx44::GetTranspose() const {
	Mtx44 ret(*this);
	ret.Transpose();
	return ret;
}

/******************************************************************************/
/*!
\brief
Return a new matrix that is an inverse

\exception DivideByZero
	thrown if the determinant of the matrix is zero
\return A new matrix
*/
/******************************************************************************/
Mtx44 Mtx44::GetInverse() const throw( DivideByZero ) {
	float a0 = a[ 0]*a[ 5] - a[ 1]*a[ 4];
    float a1 = a[ 0]*a[ 6] - a[ 2]*a[ 4];
    float a2 = a[ 0]*a[ 7] - a[ 3]*a[ 4];
    float a3 = a[ 1]*a[ 6] - a[ 2]*a[ 5];
    float a4 = a[ 1]*a[ 7] - a[ 3]*a[ 5];
    float a5 = a[ 2]*a[ 7] - a[ 3]*a[ 6];
    float b0 = a[ 8]*a[13] - a[ 9]*a[12];
    float b1 = a[ 8]*a[14] - a[10]*a[12];
    float b2 = a[ 8]*a[15] - a[11]*a[12];
    float b3 = a[ 9]*a[14] - a[10]*a[13];
    float b4 = a[ 9]*a[15] - a[11]*a[13];
    float b5 = a[10]*a[15] - a[11]*a[14];

    float det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
	if(abs(det) < Math::EPSILON)
		throw DivideByZero();
    Mtx44 inverse;
	if (Math::FAbs(det) > Math::EPSILON)
    {
        inverse.a[ 0] = + a[ 5]*b5 - a[ 6]*b4 + a[ 7]*b3;
        inverse.a[ 4] = - a[ 4]*b5 + a[ 6]*b2 - a[ 7]*b1;
        inverse.a[ 8] = + a[ 4]*b4 - a[ 5]*b2 + a[ 7]*b0;
        inverse.a[12] = - a[ 4]*b3 + a[ 5]*b1 - a[ 6]*b0;
        inverse.a[ 1] = - a[ 1]*b5 + a[ 2]*b4 - a[ 3]*b3;
        inverse.a[ 5] = + a[ 0]*b5 - a[ 2]*b2 + a[ 3]*b1;
        inverse.a[ 9] = - a[ 0]*b4 + a[ 1]*b2 - a[ 3]*b0;
        inverse.a[13] = + a[ 0]*b3 - a[ 1]*b1 + a[ 2]*b0;
        inverse.a[ 2] = + a[13]*a5 - a[14]*a4 + a[15]*a3;
        inverse.a[ 6] = - a[12]*a5 + a[14]*a2 - a[15]*a1;
        inverse.a[10] = + a[12]*a4 - a[13]*a2 + a[15]*a0;
        inverse.a[14] = - a[12]*a3 + a[13]*a1 - a[14]*a0;
        inverse.a[ 3] = - a[ 9]*a5 + a[10]*a4 - a[11]*a3;
        inverse.a[ 7] = + a[ 8]*a5 - a[10]*a2 + a[11]*a1;
        inverse.a[11] = - a[ 8]*a4 + a[ 9]*a2 - a[11]*a0;
        inverse.a[15] = + a[ 8]*a3 - a[ 9]*a1 + a[10]*a0;

        float invDet = ((float)1)/det;
        inverse.a[ 0] *= invDet;
        inverse.a[ 1] *= invDet;
        inverse.a[ 2] *= invDet;
        inverse.a[ 3] *= invDet;
        inverse.a[ 4] *= invDet;
        inverse.a[ 5] *= invDet;
        inverse.a[ 6] *= invDet;
        inverse.a[ 7] *= invDet;
        inverse.a[ 8] *= invDet;
        inverse.a[ 9] *= invDet;
        inverse.a[10] *= invDet;
        inverse.a[11] *= invDet;
        inverse.a[12] *= invDet;
        inverse.a[13] *= invDet;
        inverse.a[14] *= invDet;
        inverse.a[15] *= invDet;
    }
	return inverse;
}

/******************************************************************************/
/*!
\brief
operator* overload for matrix-matrix multiplication

\param rhs
	Matrix to multiply with
\return 
	Resulting matrix
*/
/******************************************************************************/
Mtx44 Mtx44::operator*(const Mtx44& rhs) const {
	Mtx44 ret;
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			ret.a[i * 4 + j] = a[0 * 4 + j] * rhs.a[i * 4 + 0] + a[1 * 4 + j] * rhs.a[i * 4 + 1] + a[2 * 4 + j] * rhs.a[i * 4 + 2] + a[3 * 4 + j] * rhs.a[i * 4 + 3];
	return ret;
}

/******************************************************************************/
/*!
\brief
operator+ overload for matrix-matrix addition

\param rhs
	Matrix to add with
\return 
	Resulting matrix
*/
/******************************************************************************/
Mtx44 Mtx44::operator+(const Mtx44& rhs) const {
	return Mtx44(
		a[0] + rhs.a[0],
		a[1] + rhs.a[1],
		a[2] + rhs.a[2],
		a[3] + rhs.a[3],
		a[4] + rhs.a[4],
		a[5] + rhs.a[5],
		a[6] + rhs.a[6],
		a[7] + rhs.a[7],
		a[8] + rhs.a[8],
		a[9] + rhs.a[9],
		a[10] + rhs.a[10],
		a[11] + rhs.a[11],
		a[12] + rhs.a[12],
		a[13] + rhs.a[13],
		a[14] + rhs.a[14],
		a[15] + rhs.a[15]
		);
}

/******************************************************************************/
/*!
\brief
operator= overload for assignment

\param rhs
	Matrix to assign to
\return 
	Reference to this matrix
*/
/******************************************************************************/
Mtx44& Mtx44::operator=(const Mtx44& rhs) {
	for(int i = 0; i < 16; i++)
		a[i] = rhs.a[i];
	return *this;
}

/******************************************************************************/
/*!
\brief
operator* overload for scalar multiplication

\param scalar
	float to multiply with
\return 
	Resulting matrix
*/
/******************************************************************************/
Mtx44 Mtx44::operator*(float scalar) const {
	Mtx44 ret;
	for(int i = 0; i < 16; i++)
		ret.a[i] = scalar * a[i];
	return ret;
}

/******************************************************************************/
/*!
\brief
operator* overload for matrix-vector3 multiplication

\param rhs
	Vector3 to multiply with
\return 
	Resulting vector
*/
/******************************************************************************/
Vector3 Mtx44::operator*(const Vector3& rhs) const {
	float b[4];
	for(int i = 0; i < 4; i++)
		b[i] = a[0 * 4 + i] * rhs.x + a[1 * 4 + i] * rhs.y + a[2 * 4 + i] * rhs.z + a[3 * 4 + i] * 0;
	Vector3 ret(b[0], b[1], b[2]);
	return ret;
}

/******************************************************************************/
/*!
\brief
Set Matrix to a rotation matrix about arbitrary axis

\param	degrees
	Angle of rotation, in degrees, clockwise
\param	axisX
	X-component of the rotation axis
\param	axisY
	Y-component of the rotation axis
\param	axisZ
	Z-component of the rotation axis
\exception	DivideByZero
	Thrown if rotation axis is a zero vector
*/
/******************************************************************************/
void Mtx44::SetToRotation(float degrees, float axisX, float axisY, float axisZ) throw( DivideByZero ) {
	double mag = sqrt(axisX * axisX + axisY * axisY + axisZ * axisZ);
	if(Math::FAbs((float)mag) < Math::EPSILON)
		throw DivideByZero();
	double x = axisX / mag, y = axisY / mag, z = axisZ/ mag;
	double c = cos(degrees * Math::PI / 180), s = sin(degrees * Math::PI / 180);
	a[0] = (float)(x * x * (1.f - c) + c);
	a[1] = (float)(y * x * (1.f - c) + z * s);
	a[2] = (float)(x * z * (1.f - c) - y * s);
	a[3] = 0;
	a[4] = (float)(x * y * (1.f - c) - z * s);
	a[5] = (float)(y * y * (1.f - c) + c);
	a[6] = (float)(y * z * (1.f - c) + x * s);
	a[7] = 0;
	a[8] = (float)(x * z * (1.f - c) + y * s);
	a[9] = (float)(y * z * (1.f - c) - x * s);
	a[10] = (float)(z * z * (1.f - c) + c);
	a[11] = 0;
	a[12] = 0;
	a[13] = 0;
	a[14] = 0;
	a[15] = 1;
}

/******************************************************************************/
/*!
\brief
Set this matrix to a scaling matrix with scale factors sx, sy and sz

\param sx
	scale at x-axis
\param sy
	scale at y-axis
\param sz
	scale at z-axis
*/ 
/******************************************************************************/
void Mtx44::SetToScale(float sx, float sy, float sz) {
	SetToIdentity();
	a[0] = sx;
	a[5] = sy;
	a[10] = sz;
}

/******************************************************************************/
/*!
\brief
Set this matrix to a translation matrix with translation of (x, y, z)

\param x
	translate at x-axis
\param y
	translate at y-axis
\param z
	translate at y-axis
*/
/******************************************************************************/
void Mtx44::SetToTranslation(float tx, float ty, float tz) {
	SetToIdentity();
	a[12] = tx;
	a[13] = ty;
	a[14] = tz;
}

/******************************************************************************/
/*!
\brief
Set this matrix to frustum matrix

\param left
	Frustum - left 
\param right
	Frustum - right 
\param bottom
	Frustum - bottom 
\param top
	Frustum - top 
\param nearVal
	Frustum - front
\param farVal
	Frustum - back
*/
/******************************************************************************/
void Mtx44::SetToFrustum(double left, double right, double bottom, double top, double near, double far) {
	*this = Mtx44((float)(2 * near / (right - left)), 0, 0, 0,
		0, (float)(2 * near / (top - bottom)), 0, 0,
		(float)((right + left) / (right - left)), (float)((top + bottom) / (top - bottom)), - (float)((far + near) / (far - near)), -1,
		0, 0, - (float)(2 * far * near / (far - near)), 0);
}

/******************************************************************************/
/*!
\brief Set matrix to be a lookat matrix 

\param eyeX
	eye vector x value
\param eyeY
	eye vector y value
\param eyeZ
	eye vector z value
\param centerX
	target position x value
\param centerY
	target position y value
\param centerZ
	target position z value
\param upX
	up vector x value
\param upY
	up vector y value
\param upZ
	up vector z value
*/
/******************************************************************************/
void Mtx44::SetToLookAt(double eyeX, double eyeY, double eyeZ,
				double centerX, double centerY, double centerZ,
				double upX, double upY, double upZ) {
	Vector3 f((float)(centerX - eyeX), (float)(centerY - eyeY), (float)(centerZ - eyeZ));
	f.Normalize();
	Vector3 up((float)upX, (float)upY, (float)upZ);
	up.Normalize();
	Vector3 s = f.Cross(up);
	Vector3 u = s.Cross(f);

	Mtx44 mat(s.x, u.x, -f.x, 0,
		s.y, u.y, -f.y, 0,
		s.z, u.z, -f.z, 0,
		0, 0, 0, 1);
	Mtx44 tran;
	tran.SetToTranslation(-(float)eyeX, -(float)eyeY, -(float)eyeZ);
	*this = mat * tran;
}

/******************************************************************************/
/*!
\brief Set matrix to be a perspective matrix 

\param fovy
	Field of view
\param aspect
	Aspect ratio = width : height
\param zNear
	Near plane
\param zFar
	Far plane
*/
/******************************************************************************/
void Mtx44::SetToPerspective(double fovy, double aspect, double zNear, double zFar) {
	double f = 1.0 / tan(Math::PI / 180 * fovy / 2);
	*this = Mtx44((float)(f / aspect), 0, 0, 0,
		0, (float)f, 0, 0,
		0, 0, (float)((zFar + zNear) / (zNear - zFar)), -1,
		0, 0, (float)(2 * zFar * zNear / (zNear - zFar)), 0);
}

/******************************************************************************/
/*!
\brief Setup orthogonal matrix

\param left
	View box - left 
\param right
	View box - right 
\param bottom
	View box - bottom 
\param top
	View box - top 
\param nearVal
	View box - front
\param farVal
	View box - back
*/
/******************************************************************************/
void Mtx44::SetToOrtho(double left, double right, double bottom, double top, double nearVal, double farVal) {
	*this = Mtx44(2 / (float)(right - left), 0, 0, 0,
		0, 2 / (float)(top - bottom), 0, 0,
		0, 0, - 2 / (float)(farVal - nearVal), 0,
		- (float)((right + left) / (right - left)), - (float)((top + bottom) / (top - bottom)), - (float)((farVal + nearVal) / (farVal - nearVal)), 1);
}
