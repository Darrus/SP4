#include "Overworld.h"

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

// Collider
#include "Collider\Collider_2DAABB.h"

// Utility
#include "SceneManager.h"
#include "../Animation/AnimationsContainer.h"
#include "KeyboardController.h"
#include "MatrixStack.h"
#include "../Application.h"
#include "SoundEngine\SoundEngine.h"

// Player
#include "../Player/Player.h"

bool Overworld::battle = false;

Overworld::Overworld() :
encounterRate(0.f)
{
}


Overworld::~Overworld()
{
}

void Overworld::Init()
{
	SoundEngine::GetInstance()->AddRepeatSound("Terras Theme", "Sound/Terras Theme.mp3");
	SetInit(true);

	MeshBuilder::GetInstance()->GenerateSpriteAnimation("character", 4, 9)->textureID = LoadTGA("Image//character.tga");
	MeshBuilder::GetInstance()->GenerateSpriteAnimation("moogle", 1, 2)->textureID = LoadTGA("Image//moogle.tga");
	MeshBuilder::GetInstance()->GenerateQuad("background", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//overworldBG.tga");
	MeshBuilder::GetInstance()->GenerateQuad("twee", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//twee.tga");
	MeshBuilder::GetInstance()->GenerateQuad("mountain", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//mountain.tga");
	MeshBuilder::GetInstance()->GenerateQuad("mountain_side", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//mountain_side.tga");
	MeshBuilder::GetInstance()->GenerateQuad("town", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//town.tga");
	MeshBuilder::GetInstance()->GenerateQuad("Collider", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//collider.tga");
	MeshBuilder::GetInstance()->GenerateQuad("Grid", Color(0.f, 1.f, 0.f));
	MeshBuilder::GetInstance()->GenerateText("text", 16, 16)->textureID = LoadTGA("FontData//pixelFont.tga");
	MeshBuilder::GetInstance()->GenerateQuad("paper_background", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Buttons//paper_background.tga");

	// Skybox
	MeshBuilder::GetInstance()->GenerateQuad("skybox_left", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Skybox//sky_left.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skybox_right", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Skybox//sky_right.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skybox_front", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Skybox//sky_front.tga");
	MeshBuilder::GetInstance()->GenerateQuad("skybox_back", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Skybox//sky_back.tga");
	MeshBuilder::GetInstance()->GenerateQuad("landscape", Color(1.f, 1.f, 1.f))->textureID = LoadTGA("Image//Skybox//mountain.tga");

	skybox.SetMesh(SkyBoxEntity::FRONT, MeshBuilder::GetInstance()->GetMesh("skybox_front"));
	skybox.SetMesh(SkyBoxEntity::BACK, MeshBuilder::GetInstance()->GetMesh("skybox_back"));
	skybox.SetMesh(SkyBoxEntity::LEFT, MeshBuilder::GetInstance()->GetMesh("skybox_left"));
	skybox.SetMesh(SkyBoxEntity::RIGHT, MeshBuilder::GetInstance()->GetMesh("skybox_right"));
	skybox.SetScale(Vector3(1000.f, 1000.f, 1000.f));

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

	// Background Init
	background.SetMesh(MeshBuilder::GetInstance()->GetMesh("background"));
	background.SetTextRenderMode(SpriteEntity::MODE_3D);
	background.SetPosition(Vector3(0.f, 0.f, 0.f));
	background.SetScale(Vector3(300, 300, 300.f));

	// Mountain Sky Init
	mountain.SetMesh(SkyBoxEntity::FRONT, MeshBuilder::GetInstance()->GetMesh("landscape"));
	mountain.SetMesh(SkyBoxEntity::BACK, MeshBuilder::GetInstance()->GetMesh("landscape"));
	mountain.SetMesh(SkyBoxEntity::LEFT, MeshBuilder::GetInstance()->GetMesh("landscape"));
	mountain.SetMesh(SkyBoxEntity::RIGHT, MeshBuilder::GetInstance()->GetMesh("landscape"));
	mountain.SetScale(background.GetScale());
	mountain.SetPosition(Vector3(0.f, 0.f, 20.f));

	TriggerDialogue* trigger2 = new TriggerDialogue();
	trigger2->SetPosition(Vector3(0.f, 0.f, 0.f));
	trigger2->SetScale(Vector3(10.f, 10.f, 1.f));
	trigger2->SetCollider(new CCollider_2DAABB());
	trigger2->LoadDialogue("START");
	trigger2->AttachEvent(&Player::GetInstance().eventSystem.events[Events::START_GAME]);
	EManager.AddEntity(trigger2);
	spatial.Add(trigger2);

	OverworldAsset* asset;
	Math::InitRNG();

	// Init Town
	asset = new OverworldAsset("town");
	asset->SetPosition(Vector3(0.f, 120.f, 0.1f));
	asset->SetScale(Vector3(25.f, 25.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	TriggerScene* trigger = new TriggerScene();
	trigger->Init("Town", &camera, Vector3(0.f, -130.f, 0.f));
	trigger->SetPosition(asset->GetPosition());
	trigger->SetScale(asset->GetScale());
	trigger->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(trigger);
	spatial.Add(trigger);

	asset = new StaticAsset("mountain", "mountain_side");
	asset->SetPosition(Vector3(30.f, 30.f, 0.1f));
	asset->SetScale(Vector3(50.f, 50.f, 1.f));
	asset->SetCamera(&camera);
	asset->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(asset);
	spatial.Add(asset);

	Vector3 mountPos = asset->GetPosition();
	Vector3 mountScale = asset->GetScale();
	trigger = new TriggerScene();
	trigger->Init("Cave", &camera, Vector3(0.f, -130.f, 0.f));
	trigger->SetPosition(Vector3(mountPos.x, mountPos.y - mountScale.y * 0.5f, mountPos.z));
	trigger->SetScale(Vector3(5.f, 5.f, 5.f));
	trigger->SetCollider(new CCollider_2DAABB());
	EManager.AddEntity(trigger);
	spatial.Add(trigger);

	// Assets Init
	//SpawnTrees(50.f, Vector3(30.f, 30.f, 1.f), 100);
	SpawnTrees(Vector3(-50.f, -50.f, 1.f), Vector3(50.f, 50.f, 1.f), 100);
}

void Overworld::Update()
{
	float dt = StopWatch::GetInstance()->GetDeltaTime();

	if (player.Controls())
		HandleEncounter(dt);
	spatial.Update();
	EManager.Update();
	camera.Update();

	if (KeyboardController::GetInstance()->IsKeyPressed(VK_ESCAPE))
		SceneManager::GetInstance()->quit = true;

	if (battle && camera.GetState() == CameraFollow::IDLE)
	{
        player.SetRenderFlag(false);
        SceneManager::GetInstance()->SetActiveScene("BattleScene", true);
	}
    else
    {
        player.SetRenderFlag(true);
    }

	if (KeyboardController::GetInstance()->IsKeyPressed(VK_F10))
		SceneManager::GetInstance()->SetActiveScene("PauseScene", true);
}

void Overworld::Render()
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
	mountain.Render();

	// Setup 2D pipeline then render 2D
	GraphicsManager::GetInstance()->SetOrthographicProjection(0.f, Application::GetInstance().GetWindowWidth(), 0.f, Application::GetInstance().GetWindowHeight(), -10, 10);
	GraphicsManager::GetInstance()->DetachCamera();
	EManager.RenderUI();
}

void Overworld::Exit()
{
	OverworldBase::Exit();
}

void Overworld::Pause()
{
	SoundEngine::GetInstance()->Pause("Terras Theme");
}

void Overworld::UnPause()
{
	// Camera Init
	camera.Init(80.f, 0.5f);
	camera.SetFollowSpeed(0.3f);
	camera.SetRotSpeed(200.f);
	camera.SetDistSpeed(100.f);

	camera.SetCameraTarget(player.GetPosition());
	battle = false;

	SoundEngine::GetInstance()->Play("Terras Theme");
}

void Overworld::HandleEncounter(float dt)
{
	encounterRate += dt;
	if (encounterRate > 3.f)
	{
		if (Math::RandFloatMinMax(7, 110) <= encounterRate)
		{
			battle = true;
			camera.Transition(70.f, camera.GetRotZ(), 50.f);
			encounterRate = 0.f;
		}
	}
}

void Overworld::SpawnTrees(float radius, Vector3 center, int count)
{
	OverworldAsset* asset;
	for (int i = 0; i < count; ++i)
	{
		asset = new OverworldAsset("twee");
		asset->SetScale(Vector3(10.f, 10.f, 1.f));
		asset->SetCamera(&camera);
		asset->SetCollider(new CCollider_2DAABB());
		asset->GetCollider()->SetScale(Vector3(4.f, 4.f, 1.f));

		while (true)
		{
			float t = 2 * Math::PI * Math::RandFloatMinMax(-1.f, 1.f);
			float r = Math::RandFloatMinMax(0.f, radius);

			asset->SetPosition(Vector3(r * cos(t) + center.x, r * sin(t) + center.y, 1.1f));
			CGrid* grid = spatial.GetGrid(asset->GetPosition());
			vector<EntityBase*>* entities = grid->GetListOfObject();
			bool collide = false;
			for (int i = 0; i < grid->GetObjectCount(); ++i)
			{
				if (asset->GetCollider()->CheckCollision((*entities)[i]->GetCollider()))
				{
					collide = true;
					break;
				}
			}
			if (!collide)
				break;
		}

		EManager.AddEntity(asset);
		spatial.Add(asset);
	}
}

void Overworld::SpawnTrees(Vector3 min, Vector3 max, int count)
{
	OverworldAsset* asset;
	for (int i = 0; i < count; ++i)
	{
		asset = new OverworldAsset("twee");
		asset->SetScale(Vector3(10.f, 10.f, 1.f));
		asset->SetCamera(&camera);
		asset->SetCollider(new CCollider_2DAABB());
		asset->GetCollider()->SetScale(Vector3(4.f, 4.f, 1.f));

		while (true)
		{
			float posX = Math::RandFloatMinMax(min.x, max.x);
			float posY = Math::RandFloatMinMax(min.y, max.y);

			asset->SetPosition(Vector3(posX, posY, 1.1f));
			CGrid* grid = spatial.GetGrid(asset->GetPosition());
			vector<EntityBase*>* entities = grid->GetListOfObject();
			bool collide = false;
			for (int i = 0; i < grid->GetObjectCount(); ++i)
			{
				if (asset->GetCollider()->CheckCollision((*entities)[i]->GetCollider()))
				{
					collide = true;
					break;
				}
			}
			if (!collide)
				break;
		}

		EManager.AddEntity(asset);
		spatial.Add(asset);
	}
}