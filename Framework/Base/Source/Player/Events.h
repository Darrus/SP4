#pragma once

#include "SingletonTemplate.h"

class Events
{
public:
	enum EVENTS
	{
		START_GAME,
		NUM_EVENTS
	};
	Events();
	~Events();

	bool events[NUM_EVENTS];
};

