#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Entity2D.h"
#include "CharacterInfo.h"

class Character : public Entity2D
{
	CharacterInfo* info;

public:
	Character();
	virtual ~Character();

	virtual void Update();
	virtual void Render();
	virtual void RenderUI();

	inline CharacterInfo* GetInfo() const { return info; }
};

#endif