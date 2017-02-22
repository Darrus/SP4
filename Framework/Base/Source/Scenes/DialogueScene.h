#pragma once
#include <vector>
#include <string>

#include "Scene.h"
#include "../Entity/TextEntity.h"
#include "../Entity/SpriteEntity.h"

using std::vector;
using std::string;

class DialogueScene : public Scene
{
	vector<string> dialogue;
	string targetScene;
	TextEntity* text;
	SpriteEntity* textBG;

	int textPos;

public:
	DialogueScene();
	virtual ~DialogueScene();

	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

	virtual void Pause();

	inline void SetDialogue(vector<string> dialogue)
	{ 
		this->dialogue = dialogue; 
		textPos = 0;
	}
	void SetTargetScene(string targetScene){ this->targetScene = targetScene; }
};

