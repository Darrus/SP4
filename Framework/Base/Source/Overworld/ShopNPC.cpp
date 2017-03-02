#include "ShopNPC.h"

// Scenes
#include "SceneManager.h"
#include "../Scenes/ShopDialogueScene.h"

// Utilities
#include "SoundEngine\SoundEngine.h"

ShopNPC::ShopNPC()
{
}


ShopNPC::~ShopNPC()
{
}

void ShopNPC::Update()
{
	anim.Update();
}

void ShopNPC::Interact()
{
	ShopDialogueScene* scene = dynamic_cast<ShopDialogueScene*>(SceneManager::GetInstance()->SetActiveScene("ShopDialogue", true));
	if (scene)
	{
		scene->SetDialogue(dialogue);
		scene->SetTargetScene(targetScene);
		SoundEngine::GetInstance()->Play(sfx);
	}
}
