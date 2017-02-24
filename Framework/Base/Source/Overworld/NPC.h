#ifndef NPC_H
#define NPC_H

#include <vector>
#include "OverworldEntity.h"

using std::vector;

class Mesh;

class NPC : public OverworldEntity
{
private:
	vector<string> dialogue;
	string targetScene;

public:
	NPC();
	virtual ~NPC();

	virtual void Update();


	void Interact();
	void LoadDialogue(string name);

	inline void SetTargetScene(const string& scene){ targetScene = scene; }
};

#endif