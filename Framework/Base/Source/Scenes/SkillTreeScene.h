#ifndef SKILLTREESCENE_H
#define SKILLTREESCENE_H

#include "Scene.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "../FPSCamera.h"
#include "../Entity/SpriteEntity.h"
#include "../Entity/Entity2D.h"

class SceneManager;
class TextEntity;

class SkillTreeScene : public Scene

{
public:
	SkillTreeScene();
	~SkillTreeScene();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

	Entity2D* testy;

private:
	FPSCamera camera;

};

#endif