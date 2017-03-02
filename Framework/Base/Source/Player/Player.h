#ifndef PLAYER_H
#define PLAYER_H

#include "SaveInfo.h"

class Player : public SaveInfo
{
public:
	static Player& GetInstance()
	{
		static Player player;
		return player;
	}

	Player();
	virtual ~Player();

	void Init();
	void CopyInfo(SaveInfo* save);
};

#endif