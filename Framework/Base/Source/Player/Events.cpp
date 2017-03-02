#include "Events.h"


Events::Events()
{
	for (int i = 0; i < NUM_EVENTS; ++i)
		events[i] = false;
}


Events::~Events()
{
}
