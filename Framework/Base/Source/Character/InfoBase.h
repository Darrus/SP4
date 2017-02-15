#ifndef INFO_H
#define INFO_H

#include <string>
#include "Stat.h"

using std::string;

struct InfoBase
{
	// Name of entity
	string name;
	
	// Stats of entity
	StatSystem stats;
	
	// Entity HP
	int HP;
	// Entity MP
	int MP;

	// ID
	int id;
};

#endif