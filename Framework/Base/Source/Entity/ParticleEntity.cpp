#include "ParticleEntity.h"
#include "timer.h"


void ParticleEntity::Update()
{
	Entity2D::Update();
	double dt = StopWatch::GetInstance()->GetDeltaTime();

	//Check and update lifetime 
	if (m_lifetime >= m_expire_time)
		isDone = true;
	else
		m_lifetime += dt;

	//If reached target destination
	if ((m_target - position).LengthSquared() < 50)
		isDone = true;
	//Else move
	else
	{
		position.z = 0;
		Vector3 direction = (m_target - position).Normalized();
		position += direction * m_speed *dt;
	}
}