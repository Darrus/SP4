#ifndef PARTICLE_ENTITY_H
#define PARTICLE_ENTITY_H

#include "Vector3.h"
#include "../Animation/Animation.h"
#include "Entity2D.h"

class ParticleEntity : public Entity2D
{
protected:
	Vector3 m_target;

	float m_speed;

	double m_lifetime;
	double m_expire_time;

	//Can use isDone from EntityBase
	//bool m_isActive;

public:
	//Getters and Setters
	inline Vector3 GetTargetDestination(){ return m_target; }
	inline float GetSpeed(){ return m_speed; }
	inline double GetLifetime(){ return m_lifetime; }
	inline double GetExpireTime(){ return m_expire_time; }

	inline void SetTarget(Vector3 target){ m_target = target; }
	inline void SetSpeed(float speed){ m_speed = speed; }
	//inline void SetExpireTime(double expireTime){ m_expire_time = expireTime; }//Maybe not able to set from here. Only in constructor.

	//Sprite animation settings
	/*
	virtual void PlayAnimation();
	virtual void PauseAnimation();
	virtual void StopAnimation();
	*/

	virtual void Update();
	//virtual void Render();

	ParticleEntity() :
		m_target(Vector3(500,1000,0)),
		m_speed(1.f),
		m_lifetime(0.0),
		m_expire_time(5.0){}
	ParticleEntity(double expireTime) : 
		m_expire_time(expireTime),
		m_target(Vector3(500, 1000, 0)),
		m_speed(1.f),
		m_lifetime(0.0){};
	~ParticleEntity(){}
};


#endif