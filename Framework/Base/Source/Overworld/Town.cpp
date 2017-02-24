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
	MeshBuilder::GetInstance()->GenerateQuad("skybox_left", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Skybox//skybox_left.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skybox_right", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Skybox//skybox_right.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skybox_top", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Skybox//skybox_top.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skybox_bottom", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Skybox//skybox_bottom.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skybox_front", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Skybox//skybox_front.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skybox_back", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Skybox//skybox_back.tga");

	skybox.SetMesh(SkyBoxEntity::FRONT, MeshBuilder::GetInstance()->GetMesh("skybox_front"));
	skybox.SetMesh(SkyBoxEntity::BACK, MeshBuilder::GetInstance()->GetMesh("skybox_back"));
	skybox.SetMesh(SkyBoxEntity::LEFT, MeshBuilder::GetInstance()->GetMesh("skybox_left"));
	skybox.SetMesh(SkyBoxEntity::RIGHT, MeshBuilder::GetInstance()->GetMesh("skybox_right"));
	skybox.SetMesh(SkyBoxEntity::TOP, MeshBuilder::GetInstance()->GetMesh("skybox_top"));
	skybox.SetMesh(SkyBoxEntity::BOTTOM, MeshBuilder::GetInstance()->GetMesh("skybox_bottom"));

	skybox.SetScale(Vector3(1000.f, 1000.f, 1000.f));

	// Background Init
	MeshBuilder::GetInstance()->GenerateQuad("town_background", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Town//town_background.tga");
	background.SetMesh(MeshBuilder::GetInstance()->GetMesh("town_background"));
	background.SetTextRenderMode(SpriteEntity::MODE_3D);
	background.SetPosition(Vector3(0.f, 0.f, 0.f));
	background.SetScale(Vector3(300, 300, 1.f));

	// Spatial Partition Init
	spatial.Init(300, 300, 10, 10);
	spatial.SetMesh("Grid");

	// Camera Init
	camera.Init(40.f, 0.5f);
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

	// Assets Init
	OverworldAsset* asset;
	Math::InitRNG();

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
	trigger->SetScale(Vector3(5.f, 5.f, 1.f));
	trigger->SetPosition(Vector3(asset->GetPosition().x, asset->GetPosition().y - (asset->GetScale().y * 0.5f) + (trigger->GetScale().y * 0.5f) , asset->GetPosition().z));
	trigger->SetCollider(new CCollider_2DAABB());
	trigger->SetCamera(&camera);
	trigger->SetScene("TownShop");
	EManager.AddEntity(trigger);
	spatial.Add(trigger);
}

void Town::Update()
{
	if (KeyboardController::GetInstance()->IsKeyPressed(VK_ESCAPE))
		SceneManager::GetInstance()->quit = true;

	camera.Update();
	spatial.Update();
	EManager.Update();
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

	// Setup 2D pipeline then render 2D
	GraphicsManager::GetInstance()->SetOrthographicProjection(0.f, Application::GetInstance().GetWindowWidth(), 0.f, Application::GetInstance().GetWindowHeight(), -10, 10);
	GraphicsManager::GetInstance()->DetachCamera();
	EManager.RenderUI();
}

void Town::Exit()
{
	OverworldBase::Exit();
}