#ifndef PLAYER_H
#define PLAYER_H

#include "../Party/PartySystem.h"

class Player
{
	PartySystem party;
	int gold;


public:
	Player();
	~Player();
};

#endif