#pragma once

#define ROTATION_SPEED 0.5

#include "../Camera.h"

class CameraFollow : public Camera
{
public:
	enum CAMERA_STATE
	{
		IDLE,
		TRANSITION
	};

	CameraFollow();
	virtual ~CameraFollow();

	virtual void Init(float dist, float followSpeed);
	virtual void Update();

	void Transition(float rotX, float rotZ, float dist);

	inline void SetEntityPos(Vector3 pos) { entityPos = pos; }
	inline void SetDist(float dist){ this->dist = dist; }
	inline void SetDistSpeed(float distSpeed){ this->distSpeed = distSpeed; }
	inline void SetFollowSpeed(float followSpeed) { this->followSpeed = followSpeed; }

	inline void SetRotX(float rotX){ this->rotX = rotX; }
	inline void SetRotZ(float rotZ){ this->rotZ = rotZ; }
	inline void SetRotSpeed(float rotSpeed){ this->rotSpeed = rotSpeed; }

	inline float GetRotX() { return curRotX; }
	inline float GetRotZ() { return curRotZ; }

	inline void SetState(CAMERA_STATE state) { this->state = state; }
	inline CAMERA_STATE GetState() { return this->state; }

private:
	Vector3 entityPos;
	CAMERA_STATE state;
	float curDist;
	float dist;
	float distSpeed;

	float followSpeed;
	float curRotX, curRotZ;
	float rotX, rotZ;
	float rotSpeed;

	double mouseX, mouseY;

	void Control();

};

