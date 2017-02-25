#include "TownShop.h"

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

// Trigger Areas
#include "TriggerScene.h"

TownShop::TownShop()
{
}


TownShop::~TownShop()
{
}

void TownShop::Init()
{
	// Skybox
	MeshBuilder::GetInstance()->GenerateQuad("shop_left", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//shop_left.tga");
	MeshBuilder::GetInstance()->GenerateQuad("shop_right", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//shop_right.tga");
	MeshBuilder::GetInstance()->GenerateQuad("shop_front", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//shop_front.tga");
	MeshBuilder::GetInstance()->GenerateQuad("shop_back", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//shop_back.tga");

	skybox.SetMesh(SkyBoxEntity::FRONT, MeshBuilder::GetInstance()->GetMesh("shop_front"));
	skybox.SetMesh(SkyBoxEntity::BACK, MeshBuilder::GetInstance()->GetMesh("shop_back"));
	skybox.SetMesh(SkyBoxEntity::LEFT, MeshBuilder::GetInstance()->GetMesh("shop_left"));
	skybox.SetMesh(SkyBoxEntity::RIGHT, MeshBuilder::GetInstance()->GetMesh("shop_right"));

	skybox.SetScale(Vector3(50.f, 50.f, 50.f));
	skybox.SetPosition(Vector3(0.f, 0.f, 25.f));

	// Background Init
	MeshBuilder::GetInstance()->GenerateQuad("shop_background", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//shop_background.tga");
	background.SetMesh(MeshBuilder::GetInstance()->GetMesh("shop_background"));
	background.SetTextRenderMode(SpriteEntity::MODE_3D);
	background.SetPosition(Vector3(0.f, 0.f, 0.f));
	background.SetScale(Vector3(50, 50, 1.f));

	// Spatial Partition Init
	spatial.Init(50, 50, 1, 1);
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
	player.SetCollider(new CCollider_2DAABB());
	player.GetCollider()->SetScale(Vector3(3.f, 3.f, 1.1f));
	player.SetGround(&background);
	EManager.AddEntity(&player);
	spatial.Add(&player);

	// Assets Init
	OverworldAsset* asset;
	Math::InitRNG();
	
	// NPC Init
	npc = new NPC();
	npc->GetAnimator()->AddAnimation("npc");
	npc->GetAnimator()->PlayAnimation("npc");
	npc->SetScale(Vector3(5.f, 5.f, 1.f));
	npc->SetPosition(Vector3(0.f, 20.f, 1.f));
	npc->LoadDialogue("NPC_TOWN_SHOPKEEPER");
	npc->SetTargetScene("ShopDialogue");
	npc->SetCollider(new CCollider_2DAABB());
	npc->AttachCamera(&camera);
	spatial.Add(npc);
	EManager.AddEntity(npc);

	TriggerScene* trigger = new TriggerScene();
	trigger->Init("Town", &camera, Vector3(50.f, 30.f, 0.f));
	trigger->SetScale(Vector3(5.f, 5.f, 1.f));
	trigger->SetPosition(Vector3(0.f, -25.f, 1.f));
	trigger->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(trigger);
	spatial.Add(trigger);
}

void TownShop::Update()
{
	if (KeyboardController::GetInstance()->IsKeyPressed(VK_ESCAPE))
		SceneManager::GetInstance()->quit = true;

	camera.Update();
	EManager.Update();
	spatial.Update();
}

void TownShop::Render()
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
	skybox.Render();
	background.Render();

	// Setup 2D pipeline then render 2D
	GraphicsManager::GetInstance()->SetOrthographicProjection(0.f, Application::GetInstance().GetWindowWidth(), 0.f, Application::GetInstance().GetWindowHeight(), -10, 10);
	GraphicsManager::GetInstance()->DetachCamera();
	EManager.RenderUI();
}

void TownShop::Exit()
{
	OverworldBase::Exit();
}
