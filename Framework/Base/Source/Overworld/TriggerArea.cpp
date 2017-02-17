#include "TriggerArea.h"

#include "OverworldEntity.h"

TriggerArea::TriggerArea()
{
}


TriggerArea::~TriggerArea()
{
}

void TriggerArea::HandleCollision(EntityBase* entity)
{
	OverworldEntity* player = dynamic_cast<OverworldEntity*>(entity);
}