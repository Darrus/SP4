#include "Overworld.h"

// Graphic includes
#include "GL\glew.h"
#include "LoadTGA.h"
#include "GraphicsManager.h"
#include "MeshBuilder.h"
#include "../Application.h"

// Entity
#include "../Entity/EntityFactory.h"

// Collider
#include "Collider\Collider_2DAABB.h"

// Utility
#include "SceneManager.h"
#include "../Animation/AnimationsContainer.h"
#include "KeyboardController.h"
#include "MatrixStack.h"

Overworld::Overworld() :
battle(false)
{
}


Overworld::~Overworld()
{
}

void Overworld::Init()
{
	SetInit(true);

	MeshBuilder::GetInstance()->GenerateSpriteAnimation("character", 4, 9)->textureID = LoadTGA("Image//character.tga");
	MeshBuilder::GetInstance()->GenerateQuad("background", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//overworldBG.tga");
	MeshBuilder::GetInstance()->GenerateQuad("twee", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//twee.tga");
	MeshBuilder::GetInstance()->GenerateQuad("mountain", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//mountain.tga");
	MeshBuilder::GetInstance()->GenerateQuad("Collider", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//collider.tga");
	MeshBuilder::GetInstance()->GenerateQuad("Grid", Color(0.f, 1.f, 0.f));
	MeshBuilder::GetInstance()->GenerateText("text", 16, 16)->textureID = LoadTGA("FontData//pixelFont.tga");

	EntityFactory::GetInstance()->AttachEntityManager(&EManager);
	EManager.ShowCollider(true);
	// Window Scale
	float windowWidth = Application::GetInstance().GetWindowWidth();
	float windowHeight = Application::GetInstance().GetWindowHeight();

	// Spatial Partition Init
	spatial.Init(30, 30, 10, 10);
	spatial.SetMesh("Grid");

	// Camera Init
	camera.Init(80.f, 0.5f);
	camera.SetFollowSpeed(0.3f);
	camera.SetRotSpeed(200.f);
	camera.SetDistSpeed(100.f);
	camera.SetDist(80.f);

	// Player Init
	AnimationsContainer::GetInstance()->AddAnimation("walk", new Animation("character", 1, 8, 1.f, -1));
	AnimationsContainer::GetInstance()->AddAnimation("npc", new Animation("character", 9, 17, 1.f, -1));

	player = new OverworldEntity();
	player->GetAnimator()->AddAnimation("walk");
	player->GetAnimator()->PlayAnimation("walk");
	player->SetScale(Vector3(5.f, 5.f, 1.f));
	player->SetPosition(Vector3(0.f, 0.f, 1.f));
	player->AttachCamera(&camera);
	player->SetCollider(new CCollider_2DAABB());
	player->GetCollider()->SetScale(Vector3(3.f, 3.f, 1.f));
	EManager.AddEntity(player);
	spatial.Add(player);

	npc = new NPC();
	npc->GetAnimator()->AddAnimation("npc");
	npc->GetAnimator()->PlayAnimation("npc");
	npc->SetScale(Vector3(5.f, 5.f, 1.f));
	npc->SetPosition(Vector3(0.f, 0.f, 1.f));
	npc->LoadDialogue("NPC_TOWN_SHOPKEEPER");
	EManager.AddEntity(npc);

	// Background Init
	background = new SpriteEntity(MeshBuilder::GetInstance()->GetMesh("background"));
	background->SetTextRenderMode(SpriteEntity::MODE_3D);
	background->SetPosition(Vector3(0.f, 0.f, 0.f));
	background->SetScale(Vector3(300, 300, 1.f));
	EManager.AddEntity(background);

	TriggerArea* trigger = new TriggerArea();
	trigger->SetPosition(Vector3(30.f, 10.f, 0.1f));
	trigger->SetScale(Vector3(10.f, 10.f, 1.f));
	trigger->SetCollider(new CCollider_2DAABB());
	trigger->SetCamera(&camera);
	trigger->SetScene("Shop");
	EManager.AddEntity(trigger);
	spatial.Add(trigger);

	OverworldAsset* asset;
	Math::InitRNG();

	// Assets Init
	for (int i = 0; i < 100; ++i)
	{
		float posX = Math::RandFloatMinMax(-150.f, 150.f);
		float posY = Math::RandFloatMinMax(-150.f, 150.f);
		asset = new OverworldAsset("twee");
		asset->SetPosition(Vector3(posX, posY, 1.1f));
		asset->SetScale(Vector3(10.f, 10.f, 1.f));
		asset->SetCamera(&camera);
		asset->SetCollider(new CCollider_2DAABB());
		asset->GetCollider()->SetScale(Vector3(4.f, 4.f, 1.f));
		EManager.AddEntity(asset);
		spatial.Add(asset);
	}

	asset = new OverworldAsset("mountain");
	asset->SetPosition(Vector3(30.f, 30.f, 0.1f));
	asset->SetScale(Vector3(50.f, 50.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);
}

void Overworld::Update()
{
	EManager.Update();
	camera.Update();
	spatial.Update();

	if (KeyboardController::GetInstance()->IsKeyPressed(VK_ESCAPE))
		SceneManager::GetInstance()->quit = true;

	if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
	{
		camera.Transition(70.f, 0.f, 50.f);
		battle = true;
	}

	if (battle && camera.GetState() == CameraFollow::IDLE)
	{
        player->SetRenderFlag(false);
        SceneManager::GetInstance()->SetActiveScene("BattleScene", true);
        battle = false;
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

	spatial.Render();

	// Setup 2D pipeline then render 2D
	GraphicsManager::GetInstance()->SetOrthographicProjection(0.f, Application::GetInstance().GetWindowWidth(), 0.f, Application::GetInstance().GetWindowHeight(), -10, 10);
	GraphicsManager::GetInstance()->DetachCamera();
	EManager.RenderUI();
}

void Overworld::Exit()
{
	EManager.ClearEntityList();
}

void Overworld::UnPause()
{
	camera.SetFollowSpeed(0.3f);
	camera.SetRotSpeed(200.f);
	camera.Transition(0.f, 0.f, 80.f);
}