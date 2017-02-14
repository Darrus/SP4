#ifndef CAMERA_BASE_H
#define CAMERA_BASE_H

#include "Mtx44.h"

class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase();

	virtual Mtx44 GetViewMatrix() = 0;
};

#endif // CAMERA_BASE_H