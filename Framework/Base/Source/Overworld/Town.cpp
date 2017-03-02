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
#include "SoundEngine\SoundEngine.h"

// Entities
#include "OverworldAsset.h"
#include "OverworldEntity.h"
#include "StaticAsset.h"
#include "../Entity/EntityFactory.h"

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
	SoundEngine::GetInstance()->AddRepeatSound("A Place To Call Home", "Sound/A Place To Call Home.mp3");

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
	camera.Init(80.f, 0.3f);
	camera.SetRotSpeed(200.f);
	camera.SetDistSpeed(100.f);
	camera.SetGround(&background);

	// Player Init
	MeshBuilder::GetInstance()->GenerateSpriteAnimation("character", 4, 9)->textureID = LoadTGA("Image//character.tga");
	AnimationsContainer::GetInstance()->AddAnimation("walk", new Animation("character", 1, 8, 1.f, -1));

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
	InitNPC();

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

	player.Controls();
	spatial.Update();
	EManager.Update();
	camera.Update();
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

void Town::Pause()
{
	SoundEngine::GetInstance()->Pause("A Place To Call Home");
}

void Town::UnPause()
{
	// Camera Init
	camera.Init(80.f, 0.3f);
	camera.SetRotSpeed(200.f);
	camera.SetDistSpeed(100.f);

	camera.SetCameraTarget(player.GetPosition());
	SoundEngine::GetInstance()->Play("A Place To Call Home");
}

void Town::InitBuilding()
{
	// Variables
	OverworldAsset* asset;
	TriggerScene* trigger;

	// Mesh Init
	MeshBuilder::GetInstance()->GenerateQuad("House1", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//house1.tga");
	MeshBuilder::GetInstance()->GenerateQuad("House2", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//house2.tga");

	MeshBuilder::GetInstance()->GenerateQuad("House1_side", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//house1_side.tga");
	MeshBuilder::GetInstance()->GenerateQuad("House2_side", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//house2_side.tga");

	MeshBuilder::GetInstance()->GenerateQuad("Tower", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//tower1.tga");
	MeshBuilder::GetInstance()->GenerateQuad("Tower_side", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//tower2.tga");

	MeshBuilder::GetInstance()->GenerateQuad("Shop", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//town_shop.tga");
	MeshBuilder::GetInstance()->GenerateQuad("Shop_side", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//town_shop_side.tga");

	MeshBuilder::GetInstance()->GenerateQuad("Tavern", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//tavern.tga");
	MeshBuilder::GetInstance()->GenerateQuad("Tavern_side", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//tavern_side.tga");

	// Shop Init
	asset = new StaticAsset("Shop", "Shop_side");
	asset->SetPosition(Vector3(50.f, 50.f, 1.1f));
	asset->SetScale(Vector3(25.f, 17.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	trigger = new TriggerScene();
	trigger->Init("TownShop", &camera, Vector3(0.f, -19.f, 0.f));
	trigger->SetScale(Vector3(5.f, 5.f, 1.f));
	trigger->SetPosition(Vector3(asset->GetPosition().x, asset->GetPosition().y - (asset->GetScale().y * 0.5f) + (trigger->GetScale().y * 0.5f), asset->GetPosition().z));
	trigger->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(trigger);
	spatial.Add(trigger);

	// Tavern Init
	asset = new StaticAsset("Tavern", "Tavern_side");
	asset->SetPosition(Vector3(120.f, 50.f, 1.1f));
	asset->SetScale(Vector3(25.f, 25.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	trigger = new TriggerScene();
	trigger->Init("TownTavern", &camera, Vector3(0.f, -19.f, 0.f));
	trigger->SetScale(Vector3(5.f, 5.f, 1.f));
	trigger->SetPosition(Vector3(asset->GetPosition().x - 1.f, asset->GetPosition().y - (asset->GetScale().y * 0.5f) + (trigger->GetScale().y * 0.5f), asset->GetPosition().z));
	trigger->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(trigger);
	spatial.Add(trigger);

	// House Init
	asset = new StaticAsset("House2", "House2_side");
	asset->SetPosition(Vector3(-50.f, 25.f, 1.1f));
	asset->SetScale(Vector3(25.f, 25.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	asset = new StaticAsset("Tower", "Tower_side");
	asset->SetPosition(Vector3(-100.f, 75.f, 1.1f));
	asset->SetScale(Vector3(25.f, 25.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	asset = new StaticAsset("House1", "House1_side");
	asset->SetPosition(Vector3(-130.f, -50.f, 1.1f));
	asset->SetScale(Vector3(25.f, 25.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	asset = new StaticAsset("Tower", "Tower_side");
	asset->SetPosition(Vector3(110.f, -20.f, 1.1f));
	asset->SetScale(Vector3(25.f, 25.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	asset = new StaticAsset("House2", "House2_side");
	asset->SetPosition(Vector3(60.f, -50.f, 1.1f));
	asset->SetScale(Vector3(25.f, 25.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	asset = new StaticAsset("Tower", "Tower_side");
	asset->SetPosition(Vector3(-60.f, -80.f, 1.1f));
	asset->SetScale(Vector3(25.f, 25.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);
}

void Town::InitNPC()
{
	MeshBuilder::GetInstance()->GenerateSpriteAnimation("NPC", 5, 4)->textureID = LoadTGA("Image/NPC/NPC.tga");
	AnimationsContainer::GetInstance()->AddAnimation("npc_walk_front", new Animation("NPC", 0, 4, 0.5f, -1));
	AnimationsContainer::GetInstance()->AddAnimation("npc_walk_back", new Animation("NPC", 4, 8, 0.5f, -1));
	AnimationsContainer::GetInstance()->AddAnimation("npc_walk_right", new Animation("NPC", 8, 12, 0.5f, -1));
	AnimationsContainer::GetInstance()->AddAnimation("npc_walk_left", new Animation("NPC", 12, 16, 0.5f, -1));
	AnimationsContainer::GetInstance()->AddAnimation("npc_idle_front", new Animation("NPC", 16, 16, 1.f, -1));
	AnimationsContainer::GetInstance()->AddAnimation("npc_idle_back", new Animation("NPC", 17, 17, 1.f, -1));
	AnimationsContainer::GetInstance()->AddAnimation("npc_idle_left", new Animation("NPC", 18, 18, 1.f, -1));
	AnimationsContainer::GetInstance()->AddAnimation("npc_idle_right", new Animation("NPC", 19, 19, 1.f, -1));
	SoundEngine::GetInstance()->AddSound("Moogle", "Sound/Moogle.mp3", 0.5f);

	// NPC Init
	NPC* npc = EntityFactory::GetInstance()->CreateMoogle(Vector3(40.f, -65.f, 1.f), "TOWN_NPC_CHAT1");
	npc->AttachCamera(&camera);
	npc->AddWaypoint(Vector3(40.f, -80.f, 1.f));
	npc->AddWaypoint(Vector3(40.f, -65.f, 1.f));
	spatial.Add(npc);
	EManager.AddEntity(npc);

	npc = EntityFactory::GetInstance()->CreateMoogle(Vector3(-70.f, 0.f, 1.f), "TOWN_NPC_CHAT2");
	npc->AttachCamera(&camera);
	npc->AddWaypoint(Vector3(-50.f, 0.f, 1.f));
	npc->AddWaypoint(Vector3(-70.f, 0.f, 1.f));
	spatial.Add(npc);
	EManager.AddEntity(npc);

	npc = EntityFactory::GetInstance()->CreateMoogle(Vector3(30.f, 20.f, 1.f), "TOWN_NPC_CHAT3");
	npc->AttachCamera(&camera);
	npc->AddWaypoint(Vector3(40.f, 20.f, 1.f));
	npc->AddWaypoint(Vector3(30.f, 20.f, 1.f));
	spatial.Add(npc);
	EManager.AddEntity(npc);

	npc = EntityFactory::GetInstance()->CreateMoogle(Vector3(-70.f, -60.f, 1.f), "TOWN_NPC_CHAT4");
	npc->AttachCamera(&camera);
	npc->AddWaypoint(Vector3(-80.f, -30.f, 1.f));
	npc->AddWaypoint(Vector3(-80.f, -60.f, 1.f));
	spatial.Add(npc);
	EManager.AddEntity(npc);

	npc = EntityFactory::GetInstance()->CreateMoogle(Vector3(-30.f, 90.f, 1.f), "TOWN_NPC_CHAT5");
	npc->AttachCamera(&camera);
	npc->AddWaypoint(Vector3(-30.f, 70.f, 1.f));
	npc->AddWaypoint(Vector3(-30.f, 90.f, 1.f));
	spatial.Add(npc);
	EManager.AddEntity(npc);
}