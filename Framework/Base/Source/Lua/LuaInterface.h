#pragma once

#include <lua.hpp>
#include <map>
#include <string>
#include "SingletonTemplate.h"
#include "Vector3.h"

#define Lua CLuaInterface::GetInstance()

using std::string;
using std::map;
using std::pair;

class CLuaInterface : public Singleton<CLuaInterface>
{
	friend Singleton<CLuaInterface>;
	map<string, lua_State*> luaStates;
	pair<string, lua_State*> currentState;
	lua_State *theErrorState;
	lua_State *functions;

public:
	CLuaInterface();
	virtual ~CLuaInterface();

	bool Init();
	void Run();
	void Drop();
	void DropFile(string name);
	void RegisterFunction(string name, int(*luaFunc)(lua_State*));
	void DoActiveState();

	void LoadFile(const string name);

	float Getfield(const char *key);
	void error(const char *errorCode);

	lua_State* GetActiveState();

	// Get an integer value through the Lua Interface Class
	int GetIntValue(const char* varName);
	// Get a float value through the Lua Interface Class
	float GetFloatValue(const char* varName);
	// Get String Value
	string GetStringValue(const char* varName);
	// Get Vector3 values
	Vector3 GetVector3Values(const char* varName);

	// Save an integer value through the Lua Interface Class
	void SaveIntValue(const char *fileName, const char* varName, const int value, const bool bOverwrite = NULL);
	// Save a float value through the Lua Interface Class
	void SaveFloatValue(const char *fileName, const char* varName, const float value, const bool bOverwrite = NULL);
	// Save String value
	void SaveStringValue(const char *fileName, const char* varName, const char* value, const bool bOverwrite = NULL);
	// Save Vector3 value
	void SaveVector3Values(const char *fileName, const char* varName, Vector3 value, const bool bOverwrite = NULL);

	// Get Bool Value
	bool GetBoolValue(const char* varName);
};


