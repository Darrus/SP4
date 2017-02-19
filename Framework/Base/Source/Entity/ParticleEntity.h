#ifndef PARTICLE_ENTITY_H
#define PARTICLE_ENTITY_H

#include "Vector3.h"
#include "../Animation/Animation.h"
#include "Entity2D.h"

#define LIFETIME_INFINITE -1.0

class ParticleEntity : public Entity2D
{
protected:
	double m_lifetime;
	double m_expire_time;

public:
	//Getters and Setters
	inline double GetLifetime(){ return m_lifetime; }
	inline double GetExpireTime(){ return m_expire_time; }

	//inline void SetExpireTime(double expireTime){ m_expire_time = expireTime; }//Maybe not able to set from here. Only in constructor.

	virtual void Update();
	//virtual void Render();

	ParticleEntity() :
		m_lifetime(0.0),
		m_expire_time(LIFETIME_INFINITE){}
	ParticleEntity(double expireTime) : 
		m_expire_time(expireTime),
		m_lifetime(0.0){};
	~ParticleEntity(){}
};

class Moving_ParticleEntity : public ParticleEntity
{
protected:
	Vector3 m_target;
	float m_speed;

public:
	//Getters and Setters
	inline Vector3 GetTargetDestination(){ return m_target; }
	inline float GetSpeed(){ return m_speed; }

	inline void SetTarget(Vector3 target){ m_target = target; }
	inline void SetSpeed(float speed){ m_speed = speed; }

	virtual void Update();

	Moving_ParticleEntity() : ParticleEntity(),
		m_target(Vector3(500, 1000, 0)),
		m_speed(1.f){}
	Moving_ParticleEntity(double expireTime) : ParticleEntity(expireTime),
		m_target(Vector3(500, 1000, 0)),
		m_speed(1.f){}
	~Moving_ParticleEntity(){}
};

class Exploding_ParticleEntity : public Moving_ParticleEntity
{
protected:
	//TODO:
	//Add animation to parent animator or create another one
	Animator* m_animator_at_destination;
	bool m_at_destination;
	double m_lifetime_at_destination;
	double m_expire_time_at_destination;

public:
	//Getters and Setters
	inline Animator* GetExplosionAnimator(){ return m_animator_at_destination; }
	virtual void Update();

	Exploding_ParticleEntity(){};
	virtual ~Exploding_ParticleEntity(){};
};

#endif