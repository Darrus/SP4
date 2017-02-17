#ifndef OVERWORLD_H
#define OVERWORLD_H

#include "Scene.h"
#include <vector>

#include "../Overworld/CameraFollow.h"
#include "../Overworld/OverworldEntity.h"
#include "../Overworld/OverworldAsset.h"
#include "../Overworld/TriggerArea.h"

#include "../Entity/SpriteEntity.h"

using std::vector;

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
	float lastRotX;
	SpriteEntity* background;
	OverworldEntity* player;
};

#endif