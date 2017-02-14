/******************************************************************************/
/*!
\file	MatrixStack.h
\author Wen Sheng Tang
\par	email: tang_wen_sheng\@nyp.edu.sg
\brief
Matrix Stack to replace openGL math function
*/
/******************************************************************************/
#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include <stack>
#include "Mtx44.h"

/******************************************************************************/
/*!
		Class MS:
\brief	Matrix Stack class
*/
/******************************************************************************/
class MS {
	std::stack<Mtx44> ms;
public:
	MS();
	~MS();
	const Mtx44& Top() const;
	void PopMatrix();
	void PushMatrix();
	void Clear();
	void LoadIdentity();
	void LoadMatrix(const Mtx44 &matrix);
	void MultMatrix(const Mtx44 &matrix);
	void Rotate(float degrees, float axisX, float axisY, float axisZ);
	void Scale(float scaleX, float scaleY, float scaleZ);
	void Translate(float translateX, float translateY, float translateZ);
	void Frustum(double left, double right, double	bottom, double top, double near, double far);
	void LookAt(double eyeX, double eyeY, double eyeZ,
				double centerX, double centerY, double centerZ,
				double upX, double upY, double upZ);
};

#endif
