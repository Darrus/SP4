#include <iostream>
#include "introstate.h"
#include "GL\glew.h"
#include "LoadTGA.h"

#include "../Application.h"
#include "GraphicsManager.h"
#include "MeshBuilder.h"
#include "RenderHelper.h"

#include "KeyboardController.h"
#include "SceneManager.h"

#include "../Lua/LuaInterface.h"
#include "SoundEngine\SoundEngine.h"

#include "../Entity/EntityFactory.h"

using namespace std;

CIntroState::CIntroState()
{

}
CIntroState::~CIntroState()
{

}

void CIntroState::Init()
{
	// Create and attach the camera to the scene
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	// Load all the meshes
	MeshBuilder::GetInstance()->GenerateQuad("INTROSTATE_BKGROUND", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("INTROSTATE_BKGROUND")->textureID = LoadTGA("Image//splash.tga");

	MeshBuilder::GetInstance()->GenerateText("text", 16, 16);
	MeshBuilder::GetInstance()->GetMesh("text")->textureID = LoadTGA("Image//calibri.tga");
	MeshBuilder::GetInstance()->GetMesh("text")->material.kAmbient.Set(1, 0, 0);

	Lua->LoadFile("Sound");
	SoundEngine::GetInstance()->SetMasterVolume(CLuaInterface::GetInstance()->GetFloatValue("BGM_Volume"));
	SoundEngine::GetInstance()->AddRepeatSound("splash_bgm", "Sound/splash_bgm.mp3", 1.f);
	SoundEngine::GetInstance()->Play("splash_bgm");

	float windowWidth = Application::GetInstance().GetWindowWidth();
	float windowHeight = Application::GetInstance().GetWindowHeight();

	IntroStateBackground = EntityFactory::GetInstance()->CreateSprite("INTROSTATE_BKGROUND", SpriteEntity::MODE_2D);
	IntroStateBackground->SetPosition(Vector3(windowWidth * 0.5f, windowHeight * 0.5f, 0.f));
	IntroStateBackground->SetScale(Vector3(windowWidth, windowHeight, 0.f));

	MeshBuilder::GetInstance()->GenerateSpriteAnimation("Character", 4, 9);
	MeshBuilder::GetInstance()->GetMesh("Character")->textureID = LoadTGA("Image//character.tga");

	entity.GetAnimator()->AddAnimation("WalkUp","Character", 1, 9, 1.f, -1);
	entity.GetAnimator()->PlayAnimation("WalkUp");

	cout << "CIntroState loaded\n" << endl;
}
void CIntroState::Update()
{
	if (KeyboardController::GetInstance()->IsKeyReleased(VK_SPACE))
	{
		//cout << "Loading MenuState" << endl;
		//SceneManager::GetInstance()->SetActiveScene("MenuState");
	}

	entity.Update();

	if (KeyboardController::GetInstance()->IsKeyPressed(VK_ESCAPE))
		SceneManager::GetInstance()->quit = true;
}
void CIntroState::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GraphicsManager::GetInstance()->AttachCamera(&camera);
	// Setup 2D pipeline then render 2D
	GraphicsManager::GetInstance()->SetOrthographicProjection(0, 
															  Application::GetInstance().GetWindowWidth(), 
															  0, 
															  Application::GetInstance().GetWindowHeight(), 
															  -10, 10);
	entity.Render();
	GraphicsManager::GetInstance()->DetachCamera();

	// Render the required entities
	IntroStateBackground->RenderUI();
}
void CIntroState::Exit()
{
	// Remove the meshes which are specific to CIntroState
	MeshBuilder::GetInstance()->RemoveMesh("INTROSTATE_BKGROUND");

	delete IntroStateBackground;

	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
}