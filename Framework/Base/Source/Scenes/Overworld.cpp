#include "Overworld.h"

// Graphic includes
#include "GL\glew.h"
#include "LoadTGA.h"
#include "GraphicsManager.h"
#include "MeshBuilder.h"
#include "../Application.h"

// Entity
#include "../Entity/EntityFactory.h"

// Utility
#include "SceneManager.h"
#include "KeyboardController.h"
#include "MatrixStack.h"

Overworld::Overworld()
{
}


Overworld::~Overworld()
{
}

void Overworld::Init()
{
	camera.Init(Vector3(0, 0, 100), Vector3(0, 0, -1), Vector3(0, 1, 0));
	MeshBuilder::GetInstance()->GenerateQuad("background", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//overworldBG.tga");
	MeshBuilder::GetInstance()->GenerateQuad("twee", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//twee.tga");

	EntityFactory::GetInstance()->AttachEntityManager(&EManager);

	float windowWidth = Application::GetInstance().GetWindowWidth();
	float windowHeight = Application::GetInstance().GetWindowHeight();

	background = EntityFactory::GetInstance()->CreateSprite("background", SpriteEntity::MODE_3D);
	background->SetPosition(Vector3(0.f, 0.f, 0.f));
	background->SetScale(Vector3(100, 100, 1.f));

	twee = new OverworldAsset("twee");
	twee->SetPosition(Vector3(0.f, 0.f, 0.1f));
	twee->SetScale(Vector3(10.f, 10.f, 1.f));
	twee->SetCamera(&camera);
	EManager.AddEntity(twee);
	temp = 0.f;
}

void Overworld::Update()
{
	EManager.Update();

	if (KeyboardController::GetInstance()->IsKeyPressed(VK_ESCAPE))
		SceneManager::GetInstance()->quit = true;

	if (KeyboardController::GetInstance()->IsKeyDown(VK_SPACE))
	{
		/*temp += 0.5f;
		twee->SetRotate(temp);*/

		Vector3 cameraPos = camera.GetCameraPos();

		Mtx44 mx;
		mx.SetToRotation(0.5f, 1.f, 0.f, 0.f);
		cameraPos = mx * cameraPos;
		camera.SetCameraPos(cameraPos);
		
		Vector3 front = camera.GetCameraTarget() - cameraPos;
		camera.SetCameraUp(front.Cross(Vector3(-1.f, 0.f, 0.f).Normalized()));
	}

	if (KeyboardController::GetInstance()->IsKeyDown('W'))
	{
		camera.SetCameraPos(camera.GetCameraPos() + Vector3(0.f, 1.f, 0.f));
		camera.SetCameraTarget(camera.GetCameraTarget() + Vector3(0.f, 1.f, 0.f));
	}
	if (KeyboardController::GetInstance()->IsKeyDown('S'))
	{
		camera.SetCameraPos(camera.GetCameraPos() - Vector3(0.f, 1.f, 0.f));
		camera.SetCameraTarget(camera.GetCameraTarget() - Vector3(0.f, 1.f, 0.f));
	}
	if (KeyboardController::GetInstance()->IsKeyDown('D'))
	{
		camera.SetCameraPos(camera.GetCameraPos() + Vector3(1.f, 0.f, 0.f));
		camera.SetCameraTarget(camera.GetCameraTarget() + Vector3(1.f, 0.f, 0.f));
	}
	if (KeyboardController::GetInstance()->IsKeyDown('A'))
	{
		camera.SetCameraPos(camera.GetCameraPos() - Vector3(1.f, 0.f, 0.f));
		camera.SetCameraTarget(camera.GetCameraTarget() - Vector3(1.f, 0.f, 0.f));
	}
}

void Overworld::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GraphicsManager::GetInstance()->UpdateLightUniforms();

	// Setup 3D pipeline then render 3D
	GraphicsManager::GetInstance()->SetPerspectiveProjection(4.0f / 3.0f, 0.1f, 10000.0f);
	GraphicsManager::GetInstance()->AttachCamera(&camera);
	EManager.Render();

	// Setup 2D pipeline then render 2D
	GraphicsManager::GetInstance()->SetOrthographicProjection(0.f, Application::GetInstance().GetWindowWidth(), 0.f, Application::GetInstance().GetWindowHeight(), -10, 10);
	GraphicsManager::GetInstance()->DetachCamera();
	EManager.RenderUI();
}

void Overworld::Exit()
{

}
