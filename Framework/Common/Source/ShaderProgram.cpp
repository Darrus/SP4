#include "ShaderProgram.h"
#include "GL\glew.h"

#include <iostream>
using namespace std;

ShaderProgram::ShaderProgram(unsigned int _programID) :
programID(_programID)
{
}

ShaderProgram::~ShaderProgram()
{
	if (programID != SHADER_ERROR)
		glDeleteProgram(programID);
}

unsigned int ShaderProgram::GetProgramID()
{
	return programID;
}

void ShaderProgram::SetProgramID(const unsigned int _programID)
{
	programID = _programID;
	cout << programID;
}

unsigned int ShaderProgram::AddUniform(const std::string& _name)
{
	unsigned int ID = glGetUniformLocation(programID, _name.c_str());

	if (ID != SHADER_ERROR)
		uniformMap[_name] = ID;

	return ID;
}

unsigned int ShaderProgram::GetUniform(const std::string& _name)
{
	// Return error code if the uniform does not exist
	if (uniformMap.count(_name) == 0)
		return SHADER_ERROR;

	return uniformMap[_name];
}

unsigned int ShaderProgram::GetOrAddUniform(const std::string& _name)
{
	unsigned int ID = GetUniform(_name);
	if (ID == SHADER_ERROR)
	{
		// Try to load it
		ID = AddUniform(_name);
	}

	return ID;
}

void ShaderProgram::UpdateInt(unsigned int _ID, int _value)
{
	glUniform1i(_ID, _value);
}

void ShaderProgram::UpdateFloat(unsigned int _ID, float _value)
{
	glUniform1f(_ID, _value);
}

void ShaderProgram::UpdateVector3(unsigned int _ID, const Vector3& _value)
{
	glUniform3fv(_ID, 1, &_value.x);
}

void ShaderProgram::UpdateVector3(unsigned int _ID, float* _startPtr)
{
	glUniform3fv(_ID, 1, _startPtr);
}

void ShaderProgram::UpdateMatrix44(unsigned int _ID, const Mtx44& _value)
{
	glUniformMatrix4fv(_ID, 1, GL_FALSE, &_value.a[0]);
}

void ShaderProgram::UpdateMatrix44(unsigned int _ID, float* _startPtr)
{
	glUniformMatrix4fv(_ID, 1, GL_FALSE, _startPtr);
}

void ShaderProgram::UpdateInt(const std::string& _name, int _value)
{
	unsigned int ID = GetOrAddUniform(_name);
	
	if (ID == SHADER_ERROR)
		return;

	UpdateInt(ID, _value);
}

void ShaderProgram::UpdateFloat(const std::string& _name, float _value)
{
	unsigned int ID = GetOrAddUniform(_name);

	if (ID == SHADER_ERROR)
		return;

	UpdateFloat(ID, _value);
}

void ShaderProgram::UpdateVector3(const std::string& _name, const Vector3& _value)
{
	unsigned int ID = GetOrAddUniform(_name);

	if (ID == SHADER_ERROR)
		return;

	UpdateVector3(ID, _value);
}

void ShaderProgram::UpdateVector3(const std::string& _name, float* _startPtr)
{
	unsigned int ID = GetOrAddUniform(_name);

	if (ID == SHADER_ERROR)
		return;

	UpdateVector3(ID, _startPtr);
}

void ShaderProgram::UpdateMatrix44(const std::string& _name, const Mtx44& _value)
{
	unsigned int ID = GetOrAddUniform(_name);

	if (ID == SHADER_ERROR)
		return;

	UpdateMatrix44(ID, _value);
}

void ShaderProgram::UpdateMatrix44(const std::string& _name, float* _startPtr)
{
	unsigned int ID = GetOrAddUniform(_name);

	if (ID == SHADER_ERROR)
		return;

	UpdateMatrix44(ID, _startPtr);
}