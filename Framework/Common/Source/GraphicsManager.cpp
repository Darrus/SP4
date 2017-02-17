#include "GraphicsManager.h"
#include "GL\glew.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "ShaderProgram.h"
#include "CameraBase.h"
#include "LightBase.h"

GraphicsManager::GraphicsManager() :
activeShader(nullptr),
activeCamera(nullptr),
fov(45.0)
{
}

GraphicsManager::~GraphicsManager()
{
}

void GraphicsManager::Init()
{
	// Black background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
}

ShaderProgram* GraphicsManager::LoadShader(const std::string& _name, const std::string& _vertexFilePath, const std::string& _fragmentFilePath)
{
	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(_vertexFilePath.c_str(), std::ios::in);
	if (VertexShaderStream.is_open())
	{
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else
	{
		printf("ERROR : Unable to open %s\n", _vertexFilePath.c_str());
		getchar();
		return false;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(_fragmentFilePath.c_str(), std::ios::in);
	if (FragmentShaderStream.is_open())
	{
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	else 
	{
		printf("ERROR : Unable to open %s\n", _fragmentFilePath.c_str());
		getchar();
		return false;
	}

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	
	GLint Result = GL_FALSE;
//	int InfoLogLength;
	bool compileResult = true;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", _vertexFilePath.c_str());
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	GLint isCompiled = 0;
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(VertexShaderID, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		printf("%s\n", &errorLog[0]);
		// Exit with failure.
		glDeleteShader(VertexShaderID); // Don't leak the shader.
		compileResult = false;
	}
	/*
	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
		compileResult = false;
	}
	*/

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", _fragmentFilePath.c_str());
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	GLint isFragmentCompiled = 0;
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &isFragmentCompiled);
	if (isFragmentCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(FragmentShaderID, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		printf("%s\n", &errorLog[0]);
		// Exit with failure.
		glDeleteShader(FragmentShaderID); // Don't leak the shader.
		compileResult = false;
	}

	/*
	// Compile Fragment Shader
	printf("Compiling shader : %s\n", _fragmentFilePath.c_str());
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
		compileResult = false;
	}
	*/

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(ProgramID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(ProgramID, maxLength, &maxLength, &infoLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(ProgramID);
		//Don't leak shaders either.
		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		//Use the infoLog as you see fit.
		printf("%s\n", &infoLog[0]);

		//In this simple program, we'll just leave
		compileResult = false;
	}

	//Always detach shaders after a successful link.
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	/*
	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
		compileResult = false;
	}

	*/

	// Create our actual shader program object if success
	if (compileResult)
	{
		ShaderProgram* result = new ShaderProgram(ProgramID);
		shaderMap[_name] = result;
		return result;
	}

	// Failed~ Return null
	return nullptr;
}

void GraphicsManager::SetActiveShader(const std::string& _name)
{
	if (shaderMap.count(_name) == 0)
	{
		activeShader = nullptr;
		return;
	}

	activeShader = shaderMap[_name];
	glUseProgram(activeShader->GetProgramID());
}

ShaderProgram* GraphicsManager::GetActiveShader()
{
	return activeShader;
}

void GraphicsManager::SetOrthographicProjection(double _left, double _right, double _bottom, double _top, double _nearVal, double _farVal)
{
	projectionMatrix.SetToOrtho(_left, _right, _bottom, _top, _nearVal, _farVal);
}

void GraphicsManager::SetPerspectiveProjection(double _aspect, double _zNear, double _zFar)
{
	projectionMatrix.SetToPerspective(fov, _aspect, _zNear, _zFar);
}

void GraphicsManager::SetFOV(double fov)
{
	this->fov = fov;
}

void GraphicsManager::AttachCamera(CameraBase* _cameraPtr)
{
	activeCamera = _cameraPtr;
}

void GraphicsManager::DetachCamera()
{
	activeCamera = nullptr;
}

Mtx44& GraphicsManager::GetViewMatrix()
{
	if (activeCamera == nullptr)
	{
		// Set to default if no camera available
		viewMatrix.SetToIdentity();
	}
	else
	{
		// Get the view matrix from the camera
		viewMatrix = activeCamera->GetViewMatrix();
	}
	return viewMatrix;
}

LightBase* GraphicsManager::GetLight(const std::string& _name)
{
	if (lightMap.count(_name) == 0)
		return nullptr;

	return lightMap[_name];
}

void GraphicsManager::AddLight(const std::string& _name, LightBase* _newLight)
{
	if (lightMap.count(_name) != 0)
	{
		RemoveLight(_name);
	}

	lightMap[_name] = _newLight;
}

void GraphicsManager::RemoveLight(const std::string& _name)
{
	if (lightMap.count(_name) == 0)
		return;

	delete lightMap[_name];
	lightMap.erase(_name);
}

void GraphicsManager::UpdateLights(double _dt)
{
	std::map<std::string, LightBase*>::iterator it, end;
	end = lightMap.end();
	for (it = lightMap.begin(); it != end; ++it)
	{
		it->second->Update(_dt);
	}
}

void GraphicsManager::UpdateLightUniforms()
{
	std::map<std::string, LightBase*>::iterator it, end;
	end = lightMap.end();
	for (it = lightMap.begin(); it != end; ++it)
	{
		it->second->UpdateUniforms();
	}
}

void GraphicsManager::UpdateTexture(int _slot, int _textureValue)
{
	glActiveTexture(GL_TEXTURE0 + _slot);
	glBindTexture(GL_TEXTURE_2D, _textureValue);
}

void GraphicsManager::UnbindTexture(int _slot)
{
	UpdateTexture(_slot, 0);
}