#include <fstream>
#include "NPC.h"

// Graphics
#include "GraphicsManager.h"
#include "MeshBuilder.h"
#include "RenderHelper.h"

// Scenes
#include "../Scenes/DialogueScene.h"
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

void NPC::HandleCollision(EntityBase* entity)
{
	if (entity)
		return;

	DialogueScene* scene = dynamic_cast<DialogueScene*>(SceneManager::GetInstance()->SetActiveScene("Dialogue", true));
	if (scene)
	{
		scene->SetDialogue(dialogue);
		scene->SetTargetScene(targetScene);
	}
}