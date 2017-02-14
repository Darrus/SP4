#include "Light.h"
#include "GraphicsManager.h"
#include "ShaderProgram.h"

Light::Light()
{
	type = LIGHT_POINT;
	color.Set(1, 1, 1);
	power = 0.f;
	kC = 1.f;
	kL = 0.f;
	kQ = 0.f;
	cosCutoff = cosInner = 0.8f;
	exponent = 1.f;
}

Light::~Light()
{
}

void Light::Update(double _dt)
{
	// Does nothing now~
}

void Light::UpdateUniforms()
{
	ShaderProgram* currProg = GraphicsManager::GetInstance()->GetActiveShader();

	if (currProg == nullptr)
		return;

	Vector3 lightDir(position.x, position.y, position.z);

	if (type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDirection_cameraspace = GraphicsManager::GetInstance()->GetViewMatrix() * lightDir;
		currProg->UpdateVector3(name + ".position_cameraspace", &lightDirection_cameraspace.x);
	}
	else if (type == Light::LIGHT_SPOT)
	{
		Vector3 lightPosition_cameraspace = GraphicsManager::GetInstance()->GetViewMatrix() * lightDir;
		currProg->UpdateVector3(name + ".position_cameraspace", &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = GraphicsManager::GetInstance()->GetViewMatrix() * spotDirection;
		currProg->UpdateVector3(name + ".spotDirection", &spotDirection_cameraspace.x);
	}
	else
	{
		Vector3 lightPosition_cameraspace = GraphicsManager::GetInstance()->GetViewMatrix() * lightDir;
		currProg->UpdateVector3(name + ".position_cameraspace", &lightPosition_cameraspace.x);
	}

	currProg->UpdateInt(name + ".type", type);
	currProg->UpdateVector3(name + ".color", &color.r);
	currProg->UpdateFloat(name + ".power", power);
	currProg->UpdateFloat(name + ".kC", kC);
	currProg->UpdateFloat(name + ".kL", kL);
	currProg->UpdateFloat(name + ".kQ", kQ);
	currProg->UpdateFloat(name + ".cosCutoff", cosCutoff);
	currProg->UpdateFloat(name + ".cosInner", cosInner);
	currProg->UpdateFloat(name + ".exponent", exponent);
}