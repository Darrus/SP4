#pragma once

#include "Scene.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "../FPSCamera.h"
#include "../Entity/SpriteEntity.h"
#include "../Entity/Entity2D.h"

class SceneManager;
class TextEntity;

class CIntroState : public Scene
{
public:
	CIntroState();
	~CIntroState();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

private:
	FPSCamera camera;
	SpriteEntity* IntroStateBackground;
	Entity2D entity;
};
