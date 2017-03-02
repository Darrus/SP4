#include "TavernNPC.h"

// Sound
#include "SoundEngine\SoundEngine.h"

// Scenes
#include "SceneManager.h"
#include "../Scenes/TavernDialogueScene.h"

TavernNPC::TavernNPC()
{
}


TavernNPC::~TavernNPC()
{
}

void TavernNPC::Update()
{
	anim.Update();
}

void TavernNPC::Interact()
{
	TavernDialogueScene* scene = dynamic_cast<TavernDialogueScene*>(SceneManager::GetInstance()->SetActiveScene("TavernDialogue", true));
	if (scene)
	{
		scene->SetDialogue(dialogue);
		scene->SetTargetScene(targetScene);
		SoundEngine::GetInstance()->Play(sfx);
	}
}
