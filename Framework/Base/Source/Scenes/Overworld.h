#ifndef OVERWORLD_H
#define OVERWORLD_H

#include "Scene.h"
#include "../Overworld/CameraFollow.h"
#include "../Overworld/OverworldEntity.h"
#include "../Overworld/OverworldAsset.h"
#include "../Entity/SpriteEntity.h"

class Overworld : public Scene
{
public:
	Overworld();
	virtual ~Overworld();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

	bool battle;

private:
	CameraFollow camera;
	SpriteEntity* background;
	OverworldEntity* player;
	OverworldAsset* assets[2];
};

#endif