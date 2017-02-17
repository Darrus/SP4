#ifndef SCENE_H
#define SCENE_H

#include "../../Base/Source/Entity/EntityManager.h"

class Scene
{
protected:
	bool pause = false;
	EntityManager EManager;

public:
	Scene() {}
	virtual ~Scene() {}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;

	inline void SetPause(const bool& pause){ this->pause = pause; }
	inline bool GetPause(){ return pause; }
};

#endif // SCENE_H