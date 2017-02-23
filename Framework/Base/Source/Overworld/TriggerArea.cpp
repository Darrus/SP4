#include "TriggerArea.h"

#include "OverworldPlayer.h"


TriggerArea::TriggerArea() :
trigger(false)
{
}


TriggerArea::~TriggerArea()
{
}

void TriggerArea::HandleCollision(EntityBase* entity)
{
	OverworldPlayer* player = dynamic_cast<OverworldPlayer*>(entity);
	if (player)
	{
		OnTrigger();
		trigger = true;
	}
}


void TriggerArea::OnTrigger()
{

}