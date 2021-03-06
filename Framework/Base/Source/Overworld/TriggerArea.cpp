#include "TriggerArea.h"

#include "OverworldPlayer.h"
#include "../Player/Events.h"

TriggerArea::TriggerArea() :
trigger(false), active(true),
eventTrigger(nullptr)
{
}


TriggerArea::~TriggerArea()
{
}

void TriggerArea::HandleCollision(EntityBase* entity)
{
	if (eventTrigger)
		if (*eventTrigger == true)
			return;

	OverworldPlayer* player = dynamic_cast<OverworldPlayer*>(entity);
	if (player)
	{
		OnTrigger();
		trigger = true;

		if (eventTrigger)
		{
			*eventTrigger = true;
		}
	}
}


void TriggerArea::OnTrigger()
{

}