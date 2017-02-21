#ifndef PARTICLE_ENTITY_H
#define PARTICLE_ENTITY_H

#include "Entity2D.h"

#define LIFETIME_INFINITE -1.0

//==================================================================//
//Brief: A particle that holds animations that may have a lifetime  //
//==================================================================//
class ParticleEntity : public Entity2D
{
protected:
	double m_lifetime;
	double m_expire_time;

public:
	//Getters and Setters
	inline double GetLifetime(){ return m_lifetime; }
	inline double GetExpireTime(){ return m_expire_time; }

	virtual void Update();

	ParticleEntity() :
		m_lifetime(0.0),
		m_expire_time(LIFETIME_INFINITE){}
	ParticleEntity(double expireTime) : 
		m_expire_time(expireTime),
		m_lifetime(0.0){};
	~ParticleEntity(){}
};

//==================================================================//
//Brief: A particle that moves to a set destination which then may  // 
//		 be set to disappear or stay at target destination.			//
//==================================================================//
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

//==================================================================//
//Brief: A particle that moves to a set destination which then		//
//		 changes animation that may be set to disappear or stay at  //
//		 target destination.										//
//==================================================================//
class Exploding_ParticleEntity : public Moving_ParticleEntity
{
protected:
	string m_explosion_animation_name;
	double m_lifetime_at_destination;
	double m_expire_time_at_destination;
	bool m_at_destination;

public:
	//Getters and Setters
	virtual void Update();
	inline void SetExplosionAnimation(string explosion_name){ m_explosion_animation_name = explosion_name; anim.AddAnimation(explosion_name); }

	Exploding_ParticleEntity(){};
	Exploding_ParticleEntity(double lifetime) : Moving_ParticleEntity(lifetime), 
		m_at_destination(false), 
		m_lifetime_at_destination(0.0), 
		m_expire_time_at_destination(5.0){};
	virtual ~Exploding_ParticleEntity(){};
};

namespace Create
{
	ParticleEntity* StaticParticle(string anim_sprite, Vector3 spawn_position, double lifetime = LIFETIME_INFINITE);
	Moving_ParticleEntity* MovingParticle(string anim_traveling_sprite, Vector3 spawn_position, Vector3 target_destination, float speed = 1.f, double lifetime = LIFETIME_INFINITE);
	Exploding_ParticleEntity* ExplodingParticle(string anim_traveling_sprite, string anim_explosion_sprite, Vector3 spawn_position, Vector3 target_destination, float speed = 1.f, double lifetime = LIFETIME_INFINITE);
}

#endif