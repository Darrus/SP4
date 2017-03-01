#include "Cave.h"

// Graphic includes
#include "GL\glew.h"
#include "LoadTGA.h"
#include "GraphicsManager.h"
#include "MeshBuilder.h"

// Entity
#include "../Entity/EntityFactory.h"
#include "StaticAsset.h"
#include "TriggerScene.h"
#include "TriggerDialogue.h"
#include "EnemyNPC.h"

// Collider
#include "Collider\Collider_2DAABB.h"

// Utility
#include "SceneManager.h"
#include "../Animation/AnimationsContainer.h"
#include "KeyboardController.h"
#include "MatrixStack.h"
#include "../Application.h"+

Cave::Cave()
{
}


Cave::~Cave()
{
}

void Cave::Init()
{
	// Background Init
	MeshBuilder::GetInstance()->GenerateQuad("cave_background", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Cave//cave_background.tga");
	background.SetMesh(MeshBuilder::GetInstance()->GetMesh("cave_background"));
	background.SetTextRenderMode(SpriteEntity::MODE_3D);
	background.SetPosition(Vector3(0.f, 0.f, 0.f));
	background.SetScale(Vector3(300, 300, 300.f));

	// Skybox
	MeshBuilder::GetInstance()->GenerateQuad("cave", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Cave//cave.tga");
	MeshBuilder::GetInstance()->GenerateQuad("cave_top", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Cave//cave_top.tga");
	MeshBuilder::GetInstance()->GenerateQuad("landscape", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Skybox//mountain.tga");

	skybox.SetMesh(SkyBoxEntity::FRONT, MeshBuilder::GetInstance()->GetMesh("cave"));
	skybox.SetMesh(SkyBoxEntity::BACK, MeshBuilder::GetInstance()->GetMesh("cave"));
	skybox.SetMesh(SkyBoxEntity::LEFT, MeshBuilder::GetInstance()->GetMesh("cave"));
	skybox.SetMesh(SkyBoxEntity::RIGHT, MeshBuilder::GetInstance()->GetMesh("cave"));
	skybox.SetMesh(SkyBoxEntity::TOP, MeshBuilder::GetInstance()->GetMesh("cave_top"));
	skybox.SetScale(background.GetScale());
	skybox.SetPosition(Vector3(0.f, 0.f, -background.GetScale().z * 0.5f + 70.f));

	EntityFactory::GetInstance()->AttachEntityManager(&EManager);
	EManager.ShowCollider(false);

	// Window Scale
	float windowWidth = Application::GetInstance().GetWindowWidth();
	float windowHeight = Application::GetInstance().GetWindowHeight();

	// Spatial Partition Init
	spatial.Init(300, 300, 10, 10);
	spatial.SetMesh("Grid");

	// Camera Init
	camera.Init(80.f, 0.5f);
	camera.SetFollowSpeed(0.3f);
	camera.SetRotSpeed(200.f);
	camera.SetDistSpeed(100.f);
	camera.SetGround(&background);

	// Player Init
	AnimationsContainer::GetInstance()->AddAnimation("walk", new Animation("character", 1, 8, 1.f, -1));
	AnimationsContainer::GetInstance()->AddAnimation("npc", new Animation("moogle", 0, 1, 1.f, -1));

	player.GetAnimator()->AddAnimation("walk");
	player.GetAnimator()->PlayAnimation("walk");
	player.SetScale(Vector3(5.f, 5.f, 1.f));
	player.SetPosition(Vector3(0.f, 0.f, 1.f));
	player.AttachCamera(&camera);
	player.SetCollider(new CCollider_2DAABB());
	player.GetCollider()->SetScale(Vector3(3.f, 3.f, 1.f));
	player.SetGround(&background);
	EManager.AddEntity(&player);
	spatial.Add(&player);

	// NPC Init
	EnemyNPC* npc = new EnemyNPC();
	npc->GetAnimator()->AddAnimation("npc");
	npc->GetAnimator()->PlayAnimation("npc");
	npc->SetScale(Vector3(20.f, 20.f, 1.f));
	npc->SetPosition(Vector3(0.f, 80.f, 1.f));
	npc->LoadDialogue("CAVE_NPC_BOSS");
	npc->SetCollider(new CCollider_2DAABB());
	npc->AttachCamera(&camera);
	npc->SetMoveSpeed(20.f);
	spatial.Add(npc);
	EManager.AddEntity(npc);

	// Assets Init
	OverworldAsset* asset;
	MeshBuilder::GetInstance()->GenerateQuad("boulder", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Cave//boulder.tga");
	MeshBuilder::GetInstance()->GenerateQuad("spike", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Cave//spike.tga");
	
	asset = new OverworldAsset("boulder");
	asset->SetPosition(Vector3(-100.f, 20.f, 1.1f));
	asset->SetScale(Vector3(20.f, 20.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	asset = new OverworldAsset("spike");
	asset->SetPosition(Vector3(-40.f, -50.f, 1.1f));
	asset->SetScale(Vector3(10.f, 15.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	asset = new OverworldAsset("boulder");
	asset->SetPosition(Vector3(80.f, 80.f, 1.1f));
	asset->SetScale(Vector3(20.f, 20.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	asset = new OverworldAsset("spike");
	asset->SetPosition(Vector3(30.f, -20.f, 1.1f));
	asset->SetScale(Vector3(10.f, 15.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	asset = new OverworldAsset("spike");
	asset->SetPosition(Vector3(-70.f, 80.f, 1.1f));
	asset->SetScale(Vector3(10.f, 15.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	asset = new OverworldAsset("spike");
	asset->SetPosition(Vector3(100.f, -80.f, 1.1f));
	asset->SetScale(Vector3(10.f, 15.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);
}

void Cave::Update()
{
	if (KeyboardController::GetInstance()->IsKeyPressed(VK_ESCAPE))
		SceneManager::GetInstance()->quit = true;

	float dt = StopWatch::GetInstance()->GetDeltaTime();

	player.Controls();
	spatial.Update();
	EManager.Update();
	camera.Update();
}

void Cave::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GraphicsManager::GetInstance()->UpdateLightUniforms();

	// Setup 3D pipeline then render 3D
	float windowWidth = Application::GetInstance().GetWindowWidth();
	float windowHeight = Application::GetInstance().GetWindowHeight();
	GraphicsManager::GetInstance()->SetPerspectiveProjection(windowWidth / windowHeight, 0.1f, 1000.0f);
	GraphicsManager::GetInstance()->AttachCamera(&camera);
	EManager.Render();
	spatial.Render();
	background.Render();
	skybox.Render();

	// Setup 2D pipeline then render 2D
	GraphicsManager::GetInstance()->SetOrthographicProjection(0.f, Application::GetInstance().GetWindowWidth(), 0.f, Application::GetInstance().GetWindowHeight(), -10, 10);
	GraphicsManager::GetInstance()->DetachCamera();
	EManager.RenderUI();
}

void Cave::Exit()
{

}

void Cave::UnPause()
{
	// Camera Init
	camera.Init(80.f, 0.5f);
	camera.SetFollowSpeed(0.3f);
	camera.SetRotSpeed(200.f);
	camera.SetDistSpeed(100.f);

	camera.SetCameraTarget(player.GetPosition());
}