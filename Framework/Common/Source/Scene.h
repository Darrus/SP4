#ifndef SCENE_H
#define SCENE_H

class Scene
{
	bool pause = false;

public:
	Scene() {}
	virtual ~Scene() {}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

#endif // SCENE_H