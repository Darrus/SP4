#ifndef NPC_H
#define NPC_H

#include <vector>
#include "../Entity/Entity2D.h"

using std::vector;

class Mesh;

class NPC : public Entity2D
{
private:
	vector<string> dialogue;
	int speechPointer;

public:
	NPC();
	virtual ~NPC();

	virtual void Update();
	virtual void Render();

	void LoadDialogue(string name);
};

#endif