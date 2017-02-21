#include <fstream>
#include "NPC.h"

// Graphics
#include "GraphicsManager.h"
#include "MeshBuilder.h"
#include "RenderHelper.h"

// Debug *Remember to remove*
#include "KeyboardController.h"

NPC::NPC() :
speechPointer(0)
{
	textMesh = MeshBuilder::GetInstance()->GetMesh("text");
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
}

void NPC::Update()
{
	Entity2D::Update();
	if (KeyboardController::GetInstance()->IsKeyPressed('E'))
	{
		speechPointer = (speechPointer + 1) % dialogue.size();
	}
}

void NPC::Render()
{

}

void NPC::RenderUI()
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(250.f, 250.f, 1.f);
	modelStack.Scale(50.f, 50.f, 1.f);
	RenderHelper::RenderText(textMesh, dialogue[speechPointer], Color(1.f, 1.f, 1.f));
	modelStack.PopMatrix();
}