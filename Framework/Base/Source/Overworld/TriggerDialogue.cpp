#include <fstream>
#include "TriggerDialogue.h"

// Utilities
#include "SceneManager.h"
#include "../Scenes/DialogueScene.h"


TriggerDialogue::TriggerDialogue()
{
}


TriggerDialogue::~TriggerDialogue()
{
}

void TriggerDialogue::OnTrigger()
{
	DialogueScene* scene = dynamic_cast<DialogueScene*>(SceneManager::GetInstance()->SetActiveScene("Dialogue", true));
	if (scene)
	{
		scene->SetDialogue(dialogue);
 		active = false;
	}
}

void TriggerDialogue::LoadDialogue(string fileName)
{
	string fileLoc = "Dialogue//" + fileName + ".txt";
	std::ifstream file;
	file.open(fileLoc);
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
