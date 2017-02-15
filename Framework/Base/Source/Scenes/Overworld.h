#ifndef OVERWORLD_H
#define OVERWORLD_H

#include "Scene.h"
#include "../Camera.h"
#include "../Entity/SpriteEntity.h"
#include "../Overworld/OverworldAsset.h"

class Overworld : public Scene
{
public:
	Overworld();
	virtual ~Overworld();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

	float temp;

private:
	Camera camera;
	SpriteEntity* background;
	OverworldAsset* twee;
};

#endif