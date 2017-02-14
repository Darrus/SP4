#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <map>
#include <string>
#include "Vector3.h"
#include "Mtx44.h"

class ShaderProgram
{
public:
	const unsigned int SHADER_ERROR = UINT_MAX;

	ShaderProgram(unsigned int _programID);
	~ShaderProgram();

	unsigned int GetProgramID();
	void SetProgramID(const unsigned int _programID);

	unsigned int AddUniform(const std::string& _name);
	unsigned int GetUniform(const std::string& _name);
	unsigned int GetOrAddUniform(const std::string& _name);

	void UpdateInt(unsigned int _ID, int _value);
	void UpdateFloat(unsigned int _ID, float _value);
	void UpdateVector3(unsigned int _ID, const Vector3& _value);
	void UpdateVector3(unsigned int _ID, float* _startPtr);
	void UpdateMatrix44(unsigned int _ID, const Mtx44& _value);
	void UpdateMatrix44(unsigned int _ID, float* _startPtr);

	void UpdateInt(const std::string& _name, int _value);
	void UpdateFloat(const std::string& _name, float _value);
	void UpdateVector3(const std::string& _name, const Vector3& _value);
	void UpdateVector3(const std::string& _name, float* _startPtr);
	void UpdateMatrix44(const std::string& _name, const Mtx44& _value);
	void UpdateMatrix44(const std::string& _name, float* _startPtr);

private:
	unsigned int programID;
	std::map<std::string, unsigned int> uniformMap;
};

#endif // SHADER_PROGRAM_H