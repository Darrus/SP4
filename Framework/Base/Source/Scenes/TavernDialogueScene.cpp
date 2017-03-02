#include "TavernDialogueScene.h"

// Graphics
#include "GL\glew.h"
#include "LoadTGA.h"
#include "GraphicsManager.h"
#include "Mesh.h"
#include "MeshBuilder.h"

// Utilities
#include "../Application.h"
#include "KeyboardController.h"
#include "SceneManager.h"

TavernDialogueScene::TavernDialogueScene() :
textPos(0),
dialogue_options(false)
{
}


TavernDialogueScene::~TavernDialogueScene()
{
}

void TavernDialogueScene::Init()
{
	SetInit(true);
	MeshBuilder::GetInstance()->GenerateText("text", 16, 16)->textureID = LoadTGA("FontData//pixelFont.tga");
	MeshBuilder::GetInstance()->GenerateQuad("text_background", Color(1, 1, 1))->textureID = LoadTGA("Image//Buttons//button_background.tga");
	MeshBuilder::GetInstance()->GenerateQuad("character_portrait", Color(1, 1, 1));
	MeshBuilder::GetInstance()->GetMesh("character_portrait")->textureID = LoadTGA("Image//Characters//alchemist_portrait.tga");

	text = new TextEntity(MeshBuilder::GetInstance()->GetMesh("text"), "", Color(1.f, 1.f, 1.f));
	text->SetScale(Vector3(50.f, 50.f, 0.f));
	text->SetPosition(Vector3(50.f, 125.f, 1.f));
	textBG = new SpriteEntity(MeshBuilder::GetInstance()->GetMesh("text_background"));
	textBG->SetScale(Vector3(Application::GetInstance().GetWindowWidth(), 250.f, 0.f));
	textBG->SetPosition(Vector3(Application::GetInstance().GetWindowWidth() * 0.5f, 125.f, 0.f));

	characterPortrait = new GUIObject();
	characterPortrait->SetImage(MeshBuilder::GetInstance()->GetMesh("character_portrait"));
	characterPortrait->SetActive(true);
	characterPortrait->SetPosition(250.f, 550.f);
	characterPortrait->SetScale(450.f, 600.f);

	//Dialogue options button
	ChangeScene_Button* toShopScene = new ChangeScene_Button();
	toShopScene->SetPosition(1700.f, 610.f);
	toShopScene->SetText("Hire");
	toShopScene->SetScale(300, 100);
	toShopScene->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	toShopScene->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	toShopScene->SetDesiredScene("TavernScene");
	toShopScene->SetIsOverlay(true);

	PreviousScene_Button* backToPreviousScene = new PreviousScene_Button();
	backToPreviousScene->SetPosition(1700.f, 500.f);
	backToPreviousScene->SetText("Leave");
	backToPreviousScene->SetScale(300, 100);
	backToPreviousScene->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	backToPreviousScene->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));

	Increment_Button* continue_dialogue = new Increment_Button();
	continue_dialogue->SetPosition(1700.f, 390.f);
	continue_dialogue->SetText("Talk");
	continue_dialogue->SetScale(300, 100);
	continue_dialogue->SetButtonImage(MeshBuilder::GetInstance()->GetMesh("button_background"));
	continue_dialogue->SetHighlightedImage(MeshBuilder::GetInstance()->GetMesh("button_background_alt"));
	continue_dialogue->SetIncrementAmount(1);
	continue_dialogue->SetTargetValue(textPos);

	dialogue_menu = new Menu();
	dialogue_menu->SetActive(false);
	dialogue_menu->AddButton(backToPreviousScene);
	dialogue_menu->AddButton(toShopScene);
	dialogue_menu->AddButton(continue_dialogue);
}

void TavernDialogueScene::Update()
{
	//Space to advance text. Cannot advance if there is options to choose
	if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE) && !dialogue_options)
		textPos++;

	//If is at certain line, set dialouge options to true;
	if (textPos == 2)
		dialogue_options = true;
	else
		dialogue_options = false;

	//Display dialogue options 
	if (dialogue_options)
	{
		dialogue_menu->SetActive(true);
		dialogue_menu->Update();
	}
	else
		dialogue_menu->SetActive(false);

	//Check if done with dialogue
	if (textPos >= dialogue.size())
	{
		textPos = 2;
		//SceneManager::GetInstance()->PreviousScene();
	}
	else
	{
		text->SetText(dialogue[textPos]);
	}
}

void TavernDialogueScene::Render()
{
	GraphicsManager::GetInstance()->SetOrthographicProjection(0, Application::GetInstance().GetWindowWidth(), 0, Application::GetInstance().GetWindowHeight(), -10, 10);
	textBG->RenderUI();
	text->RenderUI();
	characterPortrait->Render();
	dialogue_menu->Render();
}

void TavernDialogueScene::Exit()
{
	delete text;
}

void TavernDialogueScene::Pause()
{
	textPos = 0;
	dialogue.clear();
	targetScene = "";
}