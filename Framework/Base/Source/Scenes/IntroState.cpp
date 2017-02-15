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
#include "../Entity/Entity2D.h"

#include "Collider\Collider_2DAABB.h"

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
	camera.Init(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	// Load all the meshes
	MeshBuilder::GetInstance()->GenerateQuad("INTROSTATE_BKGROUND", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("INTROSTATE_BKGROUND")->textureID = LoadTGA("Image//splash.tga");

	MeshBuilder::GetInstance()->GenerateText("text", 16, 16);
	MeshBuilder::GetInstance()->GetMesh("text")->textureID = LoadTGA("Image//calibri.tga");
	MeshBuilder::GetInstance()->GetMesh("text")->material.kAmbient.Set(1, 0, 0);
	
	MeshBuilder::GetInstance()->GenerateQuad("Collider", Color(1.f, 0.f, 0.f));

	EntityFactory::GetInstance()->AttachEntityManager(&EManager);

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

	cout << "CIntroState loaded\n" << endl;

	menu = new Menu();

	Button *btn1 = new Button();
	btn1->SetPosition(10, 10);
	btn1->SetImage(MeshBuilder::GetInstance()->GetMesh("Character"));
	btn1->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("Character"));

	Button *btn2 = new Button();
	btn2->SetPosition(windowWidth * 0.5f, windowHeight * 0.5f);
	btn2->SetScale(500, 500);
	btn2->SetImage(MeshBuilder::GetInstance()->GetMesh("INTROSTATE_BKGROUND"));
	btn2->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("Character"));

	Entity2D* littleFucker = new Entity2D();
	littleFucker->GetAnimator()->AddAnimation("RUN", new Animation("Character", 0, 8, 1.f, -1));
	littleFucker->GetAnimator()->PlayAnimation("RUN");
	littleFucker->SetScale(Vector3(50.f, 50.f, 1.f));
	littleFucker->SetPosition(Vector3(windowWidth * 0.5f, windowHeight * 0.5f, 1.f));
	//EManager.AddEntity(littleFucker);

	menu->AddButton(btn1);
	menu->AddButton(btn2);
}
void CIntroState::Update()
{
	if (KeyboardController::GetInstance()->IsKeyReleased(VK_SPACE))
	{
		//cout << "Loading MenuState" << endl;
		//SceneManager::GetInstance()->SetActiveScene("MenuState");
	}
	
	float dt = StopWatch::GetInstance()->GetDeltaTime();
	camera.Update(dt);

	EManager.Update();

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
	menu->Render();
	EManager.Render();

	GraphicsManager::GetInstance()->DetachCamera();

	// Render the required entities
	//EManager.RenderUI();

}
void CIntroState::Exit()
{
	// Remove the meshes which are specific to CIntroState
	MeshBuilder::GetInstance()->RemoveMesh("INTROSTATE_BKGROUND");

	EManager.ClearEntityList();

	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
}

///Button Funcitons
void ButtonFunc()
{
	std::cout << "Button Function Lmao" << std::endl;
}