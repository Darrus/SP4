#include <fstream>
#include "NPC.h"

// Graphics
#include "GraphicsManager.h"
#include "MeshBuilder.h"
#include "RenderHelper.h"

// Scenes
#include "../Scenes/ShopDialogueScene.h"
#include "SceneManager.h"

NPC::NPC()
{

}


NPC::~NPC()
{
}

void NPC::LoadDialogue(string name)
{
	string fileName = "Dialogue//" + name + ".txt";
	std::ifstream file;
	file.open(fileName);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			dialogue.push_back(line);
		}
	}
	file.close();
}

void NPC::Update()
{
	OverworldEntity::Update();
}

void NPC::Interact()
{
	ShopDialogueScene* scene = dynamic_cast<ShopDialogueScene*>(SceneManager::GetInstance()->SetActiveScene(targetScene, true));
	if (scene)
	{
		scene->SetDialogue(dialogue);
		scene->SetTargetScene("Shop");
	}
}