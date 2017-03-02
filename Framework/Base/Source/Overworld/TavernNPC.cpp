#include "TavernNPC.h"

// Scenes
#include "SceneManager.h"
#include "../Scenes/TavernDialogueScene.h"

TavernNPC::TavernNPC()
{
}


TavernNPC::~TavernNPC()
{
}

void TavernNPC::Interact()
{
	TavernDialogueScene* scene = dynamic_cast<TavernDialogueScene*>(SceneManager::GetInstance()->SetActiveScene("TavernDialogue", true));
	if (scene)
	{
		scene->SetDialogue(dialogue);
		scene->SetTargetScene(targetScene);
	}
}
