#include "TextEntity.h"
#include "MeshBuilder.h"
#include "EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"

TextEntity::TextEntity(Mesh* _modelMesh, const std::string& _text, const Color& _color) :
modelMesh(_modelMesh),
position(0.0f, 0.0f, 0.0f),
scale(1.0f, 1.0f, 1.0f),
text(_text),
mode(MODE_2D),
color(_color)
{
}

TextEntity::~TextEntity()
{
}

void TextEntity::Update(double _dt)
{
	// Does nothing here, can inherit & override or create your own version of this class :D
}

void TextEntity::Render()
{
	if (mode == MODE_2D)
		return;

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderText(modelMesh, text, color);
	modelStack.PopMatrix();
}

void TextEntity::RenderUI()
{
	if (mode == MODE_3D)
		return;

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderHelper::RenderText(modelMesh, text, color);
	modelStack.PopMatrix();
}