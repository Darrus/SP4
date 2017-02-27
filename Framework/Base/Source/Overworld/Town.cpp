#include "Town.h"

// Graphic includes
#include "GL\glew.h"
#include "LoadTGA.h"
#include "GraphicsManager.h"
#include "MeshBuilder.h"

// Collider
#include "Collider\Collider_2DAABB.h"

// Animation
#include "..\Animation\AnimationsContainer.h"

// Utility
#include "..\Application.h"
#include "SceneManager.h"
#include "KeyboardController.h"

// Entities
#include "OverworldAsset.h"
#include "OverworldEntity.h"
#include "StaticAsset.h"

// Trigger Areas
#include "TriggerScene.h"

Town::Town()
{
}


Town::~Town()
{
}

void Town::Init()
{
	// Skybox Init
	MeshBuilder::GetInstance()->GenerateQuad("skybox_left", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Skybox//sky_left.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skybox_right", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Skybox//sky_right.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skybox_front", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Skybox//sky_front.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skybox_back", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Skybox//sky_back.tga");

	skybox.SetMesh(SkyBoxEntity::FRONT, MeshBuilder::GetInstance()->GetMesh("skybox_front"));
	skybox.SetMesh(SkyBoxEntity::BACK, MeshBuilder::GetInstance()->GetMesh("skybox_back"));
	skybox.SetMesh(SkyBoxEntity::LEFT, MeshBuilder::GetInstance()->GetMesh("skybox_left"));
	skybox.SetMesh(SkyBoxEntity::RIGHT, MeshBuilder::GetInstance()->GetMesh("skybox_right"));
	skybox.SetScale(Vector3(1000.f, 1000.f, 1000.f));

	// Background Init
	MeshBuilder::GetInstance()->GenerateQuad("town_background", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//town_background.tga");
	background.SetMesh(MeshBuilder::GetInstance()->GetMesh("town_background"));
	background.SetTextRenderMode(SpriteEntity::MODE_3D);
	background.SetPosition(Vector3(0.f, 0.f, 0.f));
	background.SetScale(Vector3(300.f, 300.f, 300.f));

	// Town Wall Init
	MeshBuilder::GetInstance()->GenerateQuad("wall", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//wall.tga");
	MeshBuilder::GetInstance()->GenerateQuad("gate", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//gate.tga");
	wall.SetMesh(SkyBoxEntity::FRONT, MeshBuilder::GetInstance()->GetMesh("wall"));
	wall.SetMesh(SkyBoxEntity::BACK, MeshBuilder::GetInstance()->GetMesh("gate"));
	wall.SetMesh(SkyBoxEntity::LEFT, MeshBuilder::GetInstance()->GetMesh("wall"));
	wall.SetMesh(SkyBoxEntity::RIGHT, MeshBuilder::GetInstance()->GetMesh("wall"));
	wall.SetScale(background.GetScale());
	wall.SetPosition(Vector3(0.f, 0.f, wall.GetScale().z * 0.5f - 1.f));

	// Spatial Partition Init
	spatial.Init(300, 300, 10, 10);
	spatial.SetMesh("Grid");

	// Camera Init
	camera.Init(80.f, 0.5f);
	camera.SetFollowSpeed(0.3f);
	camera.SetRotSpeed(200.f);
	camera.SetDistSpeed(100.f);

	// Player Init
	MeshBuilder::GetInstance()->GenerateSpriteAnimation("character", 4, 9)->textureID = LoadTGA("Image//character.tga");
	AnimationsContainer::GetInstance()->AddAnimation("walk", new Animation("character", 1, 8, 1.f, -1));
	AnimationsContainer::GetInstance()->AddAnimation("npc", new Animation("moogle", 0, 1, 1.f, -1));

	player.GetAnimator()->AddAnimation("walk");
	player.GetAnimator()->PlayAnimation("walk");
	player.SetScale(Vector3(5.f, 5.f, 1.f));
	player.SetPosition(Vector3(0.f, 0.f, 1.f));
	player.AttachCamera(&camera);
	player.SetGround(&background);
	player.SetCollider(new CCollider_2DAABB());
	player.GetCollider()->SetScale(Vector3(3.f, 3.f, 1.1f));
	EManager.AddEntity(&player);
	spatial.Add(&player);

	// Fountain Init
	MeshBuilder::GetInstance()->GenerateSpriteAnimation("Fountain", 1, 4)->textureID = LoadTGA("Image//Town//fountain.tga");
	AnimationsContainer::GetInstance()->AddAnimation("Fountain", new Animation("Fountain", 0, 3, 1.f, -1));
	OverworldEntity* sprite = new OverworldEntity();
	sprite->GetAnimator()->AddAnimation("Fountain");
	sprite->GetAnimator()->PlayAnimation("Fountain");
	sprite->AttachCamera(&camera);
	sprite->SetScale(Vector3(20.f, 20.f, 1.f));
	sprite->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(sprite);
	spatial.Add(sprite);

	InitBuilding();

	TriggerScene* trigger = new TriggerScene();
	trigger->Init("Overworld", &camera, Vector3(0.f, 100.f, 0.f));
	trigger->SetScale(Vector3(20.f, 20.f, 1.f));
	trigger->SetPosition(Vector3(-5.f, -155.f, 0.f));
	trigger->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(trigger);
	spatial.Add(trigger);
}

void Town::Update()
{
	if (KeyboardController::GetInstance()->IsKeyPressed(VK_ESCAPE))
		SceneManager::GetInstance()->quit = true;

	camera.Update();
	EManager.Update();
	spatial.Update();
}

void Town::Render()
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
	wall.Render();

	// Setup 2D pipeline then render 2D
	GraphicsManager::GetInstance()->SetOrthographicProjection(0.f, Application::GetInstance().GetWindowWidth(), 0.f, Application::GetInstance().GetWindowHeight(), -10, 10);
	GraphicsManager::GetInstance()->DetachCamera();
	EManager.RenderUI();
}

void Town::Exit()
{
	OverworldBase::Exit();
}

void Town::UnPause()
{
	// Camera Init
	camera.Init(80.f, 0.5f);
	camera.SetFollowSpeed(0.3f);
	camera.SetRotSpeed(200.f);
	camera.SetDistSpeed(100.f);

	camera.SetCameraTarget(player.GetPosition());
}

void Town::InitBuilding()
{
	// Assets Init
	OverworldAsset* asset;

	// Shop Init
	MeshBuilder::GetInstance()->GenerateQuad("Shop", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//town_shop.tga");
	asset = new OverworldAsset("Shop");
	asset->SetPosition(Vector3(50.f, 50.f, 1.1f));
	asset->SetScale(Vector3(25.f, 17.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	TriggerScene* trigger = new TriggerScene();
	trigger->Init("TownShop", &camera, Vector3(0.f, -19.f, 0.f));
	trigger->SetScale(Vector3(5.f, 5.f, 1.f));
	trigger->SetPosition(Vector3(asset->GetPosition().x, asset->GetPosition().y - (asset->GetScale().y * 0.5f) + (trigger->GetScale().y * 0.5f), asset->GetPosition().z));
	trigger->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(trigger);
	spatial.Add(trigger);

	// House Init
	MeshBuilder::GetInstance()->GenerateQuad("House1", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//house1.tga");
	MeshBuilder::GetInstance()->GenerateQuad("House2", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//house2.tga");
	MeshBuilder::GetInstance()->GenerateQuad("House3", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//house3.tga");
	MeshBuilder::GetInstance()->GenerateQuad("Tower1", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//tower1.tga");
	MeshBuilder::GetInstance()->GenerateQuad("Tower2", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//tower2.tga");
	MeshBuilder::GetInstance()->GenerateQuad("Tower3", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//tower3.tga");

	asset = new OverworldAsset("House1");
	asset->SetPosition(Vector3(-50.f, 25.f, 1.1f));
	asset->SetScale(Vector3(25.f, 25.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	asset = new OverworldAsset("Tower2");
	asset->SetPosition(Vector3(-100.f, 75.f, 1.1f));
	asset->SetScale(Vector3(25.f, 25.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	asset = new OverworldAsset("House3");
	asset->SetPosition(Vector3(-130.f, -50.f, 1.1f));
	asset->SetScale(Vector3(25.f, 25.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	asset = new OverworldAsset("Tower1");
	asset->SetPosition(Vector3(110.f, -20.f, 1.1f));
	asset->SetScale(Vector3(25.f, 25.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	asset = new OverworldAsset("House2");
	asset->SetPosition(Vector3(60.f, -50.f, 1.1f));
	asset->SetScale(Vector3(25.f, 25.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	asset = new OverworldAsset("House3");
	asset->SetPosition(Vector3(120.f, 50.f, 1.1f));
	asset->SetScale(Vector3(25.f, 25.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	asset = new StaticAsset("Tower1", "Tower2");
	asset->SetPosition(Vector3(-60.f, -80.f, 1.1f));
	asset->SetScale(Vector3(25.f, 25.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);
}