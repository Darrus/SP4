#include "RenderHelper.h"
#include "Mesh.h"
#include "GraphicsManager.h"
#include "ShaderProgram.h"
#include "MatrixStack.h"
#include "../../Base/Source/Application.h"

void RenderHelper::RenderMesh(Mesh* _mesh)
{
	// Get all our transform matrices & update shader
	Mtx44 MVP;
	MVP = GraphicsManager::GetInstance()->GetProjectionMatrix() * GraphicsManager::GetInstance()->GetViewMatrix() * GraphicsManager::GetInstance()->GetModelStack().Top();
	Mtx44 projection = GraphicsManager::GetInstance()->GetProjectionMatrix();
	ShaderProgram* currProg = GraphicsManager::GetInstance()->GetActiveShader();
	currProg->UpdateMatrix44("MVP", &MVP.a[0]);

	// Disable lighting stuff
	currProg->UpdateInt("lightEnabled", 0);

	// Update textures first if available
	if (_mesh->textureID > 0)
	{
		currProg->UpdateInt("colorTextureEnabled", 1);
		GraphicsManager::GetInstance()->UpdateTexture(0, _mesh->textureID);
		currProg->UpdateInt("colorTexture", 0);
	}
	else
	{
		currProg->UpdateInt("colorTextureEnabled", 0);
	}

	// Do actual rendering
	_mesh->Render();

	// Unbind texture for safety (in case next render call uses it by accident)
	if (_mesh->textureID > 0)
	{
		GraphicsManager::GetInstance()->UnbindTexture(0);
	}
}

void RenderHelper::RenderMeshWithLight(Mesh* _mesh)
{
	// Get all our transform matrices & update shader
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = GraphicsManager::GetInstance()->GetProjectionMatrix() * GraphicsManager::GetInstance()->GetViewMatrix() * GraphicsManager::GetInstance()->GetModelStack().Top();
	ShaderProgram* currProg = GraphicsManager::GetInstance()->GetActiveShader();
	currProg->UpdateMatrix44("MVP", &MVP.a[0]);

	// Update light stuff
	currProg->UpdateInt("lightEnabled", 1);
	modelView = GraphicsManager::GetInstance()->GetViewMatrix() * GraphicsManager::GetInstance()->GetModelStack().Top();
	currProg->UpdateMatrix44("MV", &modelView.a[0]);
	modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
	currProg->UpdateMatrix44("MV_inverse_transpose", &modelView.a[0]);

	//load material
	currProg->UpdateVector3("material.kAmbient", &_mesh->material.kAmbient.r);
	currProg->UpdateVector3("material.kDiffuse", &_mesh->material.kDiffuse.r);
	currProg->UpdateVector3("material.kSpecular", &_mesh->material.kSpecular.r);
	currProg->UpdateFloat("material.kShininess", _mesh->material.kShininess);
	
	// Update textures first if available
	if (_mesh->textureID > 0)
	{
		currProg->UpdateInt("colorTextureEnabled", 1);
		GraphicsManager::GetInstance()->UpdateTexture(0, _mesh->textureID);
		currProg->UpdateInt("colorTexture", 0);
	}
	else
	{
		currProg->UpdateInt("colorTextureEnabled", 0);
	}

	// Do actual rendering
	_mesh->Render();

	// Unbind texture for safety (in case next render call uses it by accident)
	if (_mesh->textureID > 0)
	{
		GraphicsManager::GetInstance()->UnbindTexture(0);
	}
}

void RenderHelper::RenderText(Mesh* _mesh, const std::string& _text, Color _color)
{
	// Trivial Rejection : Unable to render without mesh or texture
	if (!_mesh || _mesh->textureID <= 0)
		return;

	ShaderProgram* currProg = GraphicsManager::GetInstance()->GetActiveShader();

	currProg->UpdateInt("textEnabled", 1);
	currProg->UpdateVector3("textColor", &_color.r);
	currProg->UpdateInt("lightEnabled", 0);
	currProg->UpdateInt("colorTextureEnabled", 1);
	
	currProg->UpdateInt("colorTextureEnabled", 1);
	GraphicsManager::GetInstance()->UpdateTexture(0, _mesh->textureID);
	currProg->UpdateInt("colorTexture", 0);

	for (float i = 0; i < _text.length(); ++i)
	{
		Mtx44 characterSpacing, MVP;
		float offset = Application::GetInstance().GetCharacterOffset(_text[i]);
		offset *= 0.01;
		characterSpacing.SetToTranslation((i + offset) * 0.6f, 0, 1.f); //1.0f is the spacing of each character, you may change this value
		MVP = GraphicsManager::GetInstance()->GetProjectionMatrix() * GraphicsManager::GetInstance()->GetViewMatrix() * GraphicsManager::GetInstance()->GetModelStack().Top() * characterSpacing;
		currProg->UpdateMatrix44("MVP", &MVP.a[0]);

		_mesh->Render((unsigned)_text[i] * 6, 6);
	}

	GraphicsManager::GetInstance()->UnbindTexture(0);
	currProg->UpdateInt("textEnabled", 0);
}

void RenderHelper::RenderSprite(Mesh* _mesh, unsigned frame)
{
	// Get all our transform matrices & update shader
	Mtx44 MVP;
	MVP = GraphicsManager::GetInstance()->GetProjectionMatrix() * GraphicsManager::GetInstance()->GetViewMatrix() * GraphicsManager::GetInstance()->GetModelStack().Top();
	Mtx44 projection = GraphicsManager::GetInstance()->GetProjectionMatrix();
	ShaderProgram* currProg = GraphicsManager::GetInstance()->GetActiveShader();
	currProg->UpdateMatrix44("MVP", &MVP.a[0]);

	// Disable lighting stuff
	currProg->UpdateInt("lightEnabled", 0);

	// Update textures first if available
	if (_mesh->textureID > 0)
	{
		currProg->UpdateInt("colorTextureEnabled", 1);
		GraphicsManager::GetInstance()->UpdateTexture(0, _mesh->textureID);
		currProg->UpdateInt("colorTexture", 0);
	}
	else
	{
		currProg->UpdateInt("colorTextureEnabled", 0);
	}

	// Do actual rendering
	_mesh->Render(frame);

	// Unbind texture for safety (in case next render call uses it by accident)
	if (_mesh->textureID > 0)
	{
		GraphicsManager::GetInstance()->UnbindTexture(0);
	}
}

void RenderHelper::RenderItem(Mesh* _item, float pos_x, float pos_y, float scale_x, float scale_y)
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(pos_x, pos_y, 0.0f);
	modelStack.Scale(scale_x, scale_y, 1.f);
	RenderMesh(_item);
	modelStack.PopMatrix();
}