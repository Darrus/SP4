#include "ParticleEntity.h"
#include "timer.h"
#include "MeshBuilder.h"
#include "EntityManager.h"

void ParticleEntity::Update()
{
	Entity2D::Update();
	double dt = StopWatch::GetInstance()->GetDeltaTime();

	//Check and update lifetime 
	if (m_expire_time != LIFETIME_INFINITE)
	{
		if (m_lifetime >= m_expire_time)
			isDone = true;
		else
			m_lifetime += dt;
	}
}

void Moving_ParticleEntity::Update()
{
	ParticleEntity::Update();
	double dt = StopWatch::GetInstance()->GetDeltaTime();

	//If reached target destination
	if ((m_target - position).LengthSquared() < 50)
		isDone = true;
	//Else move
	else
	{
		position.z = 0;
		Vector3 direction = (m_target - position).Normalized();
		position += direction * m_speed * (float)dt;
	}
}

void Exploding_ParticleEntity::Update()
{
	ParticleEntity::Update();
	double dt = StopWatch::GetInstance()->GetDeltaTime();

	//If has not reached target destination
	if (m_at_destination)
	{
		if (m_expire_time_at_destination != LIFETIME_INFINITE)
		{
			if (m_lifetime_at_destination >= m_expire_time_at_destination)
				isDone = true;
			else
				m_lifetime_at_destination += dt;
		}
		else
			isDone = true;
	}
	else
	{
		if ((m_target - position).LengthSquared() < 50)
		{
			m_at_destination = true;
			anim.PlayAnimation("destination_sprite");
		}
		else
		{
			position.z = 0;
			Vector3 direction = (m_target - position).Normalized();
			position += direction * m_speed * (float)dt;
		}
	}
}

namespace Create
{
	//TODO:
	//Hard to add animation currently because animations are not held in the graphics manager
	//Otherwise I have to set the animation from 
	ParticleEntity* StaticParticle(EntityManager* entitymanger, string anim_sprite, Vector3 spawn_position, double lifetime = LIFETIME_INFINITE)
	{
		//TODO:
		//Use a fetchGO instead
		ParticleEntity* particle = new ParticleEntity(lifetime);
		//particle->GetAnimator()->AddAnimation("travelling_sprite", new Animation(anim_sprite, 0, 8, 1.f, -1));
		particle->SetPosition(spawn_position);
		return particle;
	};

	Moving_ParticleEntity* MovingParticle(EntityManager* entitymanger, string anim_traveling_sprite, string anim_destination_sprite, Vector3 spawn_position, Vector3 target_destination, float speed = 1.f, double lifetime = LIFETIME_INFINITE)
	{
		Moving_ParticleEntity* particle = dynamic_cast<Moving_ParticleEntity*>(StaticParticle(entitymanger, anim_traveling_sprite, spawn_position, lifetime));
		//particle->GetAnimator()->AddAnimation("destination_sprite", new Animation(anim_destination_sprite, 0, 8, 1.f, -1));
		particle->SetTarget(target_destination);
		particle->SetSpeed(speed);
		return particle;
	};
}
