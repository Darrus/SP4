#ifndef SCENE_H
#define SCENE_H

#include "../../Base/Source/Entity/EntityManager.h"

class Scene
{
protected:
	EntityManager EManager;
	bool init;

public:
	Scene() : init(false) {}
	virtual ~Scene() {}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;

	virtual void Pause(){}
	virtual void UnPause(){}

	inline void SetInit(const bool& init) { this->init = init; }
	inline bool GetInit() { return this->init; }
};

#endif // SCENE_H