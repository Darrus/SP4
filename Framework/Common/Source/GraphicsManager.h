#ifndef GRAPHICS_MANAGER_H
#define GRAPHICS_MANAGER_H

#include "SingletonTemplate.h"
#include "Mtx44.h"
#include "MatrixStack.h"
#include <map>
#include <string>

class ShaderProgram;
class CameraBase;
class LightBase;

class GraphicsManager : public Singleton<GraphicsManager>
{
	friend Singleton<GraphicsManager>;
public:
	void Init();

	// Basic Shader Loading and Swapping
	ShaderProgram* LoadShader(const std::string& _name, const std::string& _vertexFilePath, const std::string& _fragmentFilePath);
	void SetActiveShader(const std::string& _name);
	ShaderProgram* GetActiveShader();

	// Setting Projection Matrix
	void SetOrthographicProjection(double _left, double _right, double _bottom, double _top, double _nearVal, double _farVal);
	void SetPerspectiveProjection(double _aspect, double _zNear, double _zFar);
	inline Mtx44& GetProjectionMatrix(){ return projectionMatrix;  };

	void SetFOV(double fov);

	// Handling Camera
	void AttachCamera(CameraBase* _cameraPtr);
	void DetachCamera();
	inline CameraBase* GetActiveCamera(){ return activeCamera; };
	Mtx44& GetViewMatrix();

	// Model Stack Modification
	inline MS& GetModelStack(){ return modelStack; };

	// Handling Lights
	LightBase* GetLight(const std::string& _name);
	void AddLight(const std::string& _name, LightBase* _newLight);
	void RemoveLight(const std::string& _name);
	void UpdateLights(double _dt);
	void UpdateLightUniforms();

	// OpenGL Toggles - WIP
	void UpdateTexture(int _slot, int _textureValue);
	void UnbindTexture(int _slot);

private:
	GraphicsManager();
	~GraphicsManager();

	std::map<std::string, LightBase*> lightMap;

	std::map<std::string, ShaderProgram*> shaderMap;
	ShaderProgram* activeShader;

	unsigned vertexArrayID;

	Mtx44 projectionMatrix;
	Mtx44 viewMatrix;
	MS modelStack;

	CameraBase* activeCamera;
	double fov;
};

#endif // GRAPHICS_MANAGER_H