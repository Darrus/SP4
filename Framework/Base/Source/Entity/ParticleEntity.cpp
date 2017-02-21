#include "ParticleEntity.h"
#include "timer.h"
#include "MeshBuilder.h"

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
	Entity2D::Update();
	double dt = StopWatch::GetInstance()->GetDeltaTime();

	//If reached target destination
	if ((m_target - position).LengthSquared() < 50)
	{
		//Check and update lifetime 
		if (m_expire_time != LIFETIME_INFINITE)
		{
			if (m_lifetime >= m_expire_time)
				isDone = true;
			else
				m_lifetime += dt;
		}
	}
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
	Entity2D::Update();
	double dt = StopWatch::GetInstance()->GetDeltaTime();

	if (m_at_destination)
	{
		if (m_expire_time_at_destination != LIFETIME_INFINITE)
		{
			if (m_lifetime_at_destination >= m_expire_time_at_destination)
				isDone = true;
			else if (anim.GetDone())
				isDone = true;
			else
				m_lifetime_at_destination += dt;
		}
	}
	else
	{
		if ((m_target - position).LengthSquared() < 50)
		{
			m_at_destination = true;
			anim.PlayAnimation(m_explosion_animation_name);
		}
		else
		{
			position.z = 0;
			Vector3 direction = (m_target - position).Normalized();
			position += direction * m_speed * (float)dt;
		}
	}
}

//Create namespace functions
ParticleEntity* Create::StaticParticle(string anim_sprite, Vector3 spawn_position, double lifetime)
{
	ParticleEntity* particle = new ParticleEntity(lifetime);
	particle->GetAnimator()->AddAnimation(anim_sprite);
	particle->GetAnimator()->PlayAnimation(anim_sprite);
	particle->SetPosition(spawn_position);
	particle->SetScale(Vector3(50.f, 50.f, 1.f));
	return particle;
};

Moving_ParticleEntity* Create::MovingParticle(string anim_traveling_sprite, Vector3 spawn_position, Vector3 target_destination, float speed, double lifetime)
{
	Moving_ParticleEntity* particle = new Moving_ParticleEntity(lifetime);
	particle->GetAnimator()->AddAnimation(anim_traveling_sprite);
	particle->GetAnimator()->PlayAnimation(anim_traveling_sprite);
	particle->SetPosition(spawn_position);
	particle->SetTarget(target_destination);
	particle->SetSpeed(speed);
	particle->SetScale(Vector3(50, 50, 1));
	return particle;
};

Exploding_ParticleEntity* Create::ExplodingParticle(string anim_traveling_sprite, string anim_explosion_sprite, Vector3 spawn_position, Vector3 target_destination, float speed, double lifetime)
{
	Exploding_ParticleEntity* particle = new Exploding_ParticleEntity(lifetime);
	particle->GetAnimator()->AddAnimation(anim_traveling_sprite);
	particle->GetAnimator()->PlayAnimation(anim_traveling_sprite);
	particle->SetExplosionAnimation(anim_explosion_sprite);
	particle->SetTarget(target_destination);
	particle->SetSpeed(speed);
	particle->SetPosition(spawn_position);
	particle->SetScale(Vector3(50, 50, 1));

	return particle;
}
