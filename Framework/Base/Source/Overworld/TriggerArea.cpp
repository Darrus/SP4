#include "TriggerArea.h"

#include "OverworldPlayer.h"


TriggerArea::TriggerArea() :
trigger(false), active(true)
{
}


TriggerArea::~TriggerArea()
{
}

void TriggerArea::HandleCollision(EntityBase* entity)
{
	if (!active)
		return;

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