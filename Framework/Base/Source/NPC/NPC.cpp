#include <fstream>
#include "NPC.h"

// Graphics
#include "GraphicsManager.h"
#include "MeshBuilder.h"
#include "RenderHelper.h"

NPC::NPC() : speechPointer(0)
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
	Entity2D::Update();
}

void NPC::Render()
{

}