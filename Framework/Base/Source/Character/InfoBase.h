#ifndef INFO_H
#define INFO_H

#include <string>
#include "Stat.h"

using std::string;

class InfoBase
{
public:
    InfoBase(){}
    ~InfoBase(){}

	// Name of entity
	string name;
	
	// Stats of entity
	StatSystem stats;
	
	// Entity HP
	int HP = 0;
	// Entity MP
	int MP = 0;

	// ID
	int id = 0;
};

#endif