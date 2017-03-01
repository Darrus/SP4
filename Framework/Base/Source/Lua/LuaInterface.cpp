#include <iostream>
#include "LuaInterface.h"

using std::cout;
using std::endl;

CLuaInterface::CLuaInterface() :
functions(nullptr)
{
	functions = lua_open();
	if (functions)
	{
		luaL_openlibs(functions);
		luaL_dofile(functions, "Script//LuaFunctions.lua");
	}
}


CLuaInterface::~CLuaInterface()
{
	Drop();
}

float CLuaInterface::Getfield(const char *key)
{
	int result;
	lua_pushstring(currentState.second, key);
	lua_gettable(currentState.second, -2);
	if (!lua_isnumber(currentState.second, -1))
		error("error101");
	result = (int)lua_tonumber(currentState.second, -1);
	lua_pop(currentState.second, 1);
	return result;
}

// Get an integer value through the Lua Interface Class
int CLuaInterface::GetIntValue(const char* varName)
{
	lua_getglobal(currentState.second, varName);
	return lua_tointeger(currentState.second, -1);
}

// Get a float value through the Lua Interface Class
float CLuaInterface::GetFloatValue(const char* varName)
{
	lua_getglobal(currentState.second, varName);
	return (float)lua_tonumber(currentState.second, -1);
}

string CLuaInterface::GetStringValue(const char* varName)
{
	lua_getglobal(currentState.second, varName);
	const char *title = lua_tostring(currentState.second, -1);
	string result = title;
	return result;
}

vector<string> CLuaInterface::GetStringTable(const char* varName)
{
	vector<string> container;
	lua_getglobal(currentState.second, varName);
	if (lua_isnil(currentState.second, -1)) {
		return container;
	}
	lua_pushnil(currentState.second);

	while (lua_next(currentState.second, -2))
	{
		const char *temp = lua_tostring(currentState.second, -1);
		string convert = temp;
		container.push_back(convert);
		lua_pop(currentState.second, 1);
	}

	return container;
}

Vector3 CLuaInterface::GetVector3Values(const char* varName)
{
	lua_getglobal(currentState.second, varName);
	lua_rawgeti(currentState.second, -1, 1);
	float x = (float)lua_tonumber(currentState.second, -1);
	lua_pop(currentState.second, 1);
	lua_rawgeti(currentState.second, -1, 2);
	float y = (float)lua_tonumber(currentState.second, -1);
	lua_pop(currentState.second, 1);
	lua_rawgeti(currentState.second, -1, 3);
	float z = (float)lua_tonumber(currentState.second, -1);
	lua_pop(currentState.second, 1);

	return Vector3(x, y, z);
}

// Save an integer value through the Lua Interface Class
void CLuaInterface::SaveIntValue(const char *fileName, const char* varName, const int value, const bool bOverwrite)
{
	lua_getglobal(functions, "SaveToLuaFile");
	char file[80];
	sprintf(file, "Script/%s.lua", fileName);
	char outputString[80];
	sprintf(outputString, "%s = %d\n", varName, value);
	lua_pushstring(functions, file);
	lua_pushstring(functions, outputString);
	lua_pushinteger(functions, bOverwrite);
	lua_call(functions, 3, 0); cout << "..................";
}

// Save a float value through the Lua Interface Class
void CLuaInterface::SaveFloatValue(const char *fileName, const char* varName, const float value, const bool bOverwrite)
{
	lua_getglobal(functions, "SaveToLuaFile");
	char file[80];
	sprintf(file, "Script/%s.lua", fileName);
	char outputString[80];
	sprintf(outputString, "%s = %6.4f\n", varName, value);
	lua_pushstring(functions, file);
	lua_pushstring(functions, outputString);
	lua_pushinteger(functions, bOverwrite);
	lua_call(functions, 3, 0); cout << "..................";
}

void CLuaInterface::SaveStringValue(const char *fileName, const char* varName, const char* value, const bool bOverwrite)
{
	lua_getglobal(functions, "SaveToLuaFile");
	char file[80];
	sprintf(file, "Script/%s.lua", fileName);
	char outputString[80];
	sprintf(outputString, "%s = \"%s\"\n", varName, value);
	lua_pushstring(functions, file);
	lua_pushstring(functions, outputString);
	lua_pushinteger(functions, bOverwrite);
	lua_call(functions, 3, 0); cout << "..................";
}

// Save string as a table
void CLuaInterface::SaveStringTable(const char *fileName, const char* varName, const char* value, const bool bOverwrite)
{
	lua_getglobal(functions, "SaveToLuaFile");
	char file[80];
	sprintf(file, "Script/%s.lua", fileName);
	char outputString[80];
	sprintf(outputString, "%s = { %s } \n", varName, value);
	lua_pushstring(functions, file);
	lua_pushstring(functions, outputString);
	lua_pushinteger(functions, bOverwrite);
	lua_call(functions, 3, 0); cout << "..................";
}

void CLuaInterface::SaveVector3Values(const char *fileName, const char* varName, Vector3 value, const bool bOverwrite)
{
	lua_getglobal(functions, "SaveToLuaFile");
	char file[80];
	sprintf(file, "Script/%s.lua", fileName);
	char outputString[80];
	sprintf(outputString, "%s = {%6.4f, %6.4f, %6.4f}\n", varName, value.x, value.y, value.z);
	lua_pushstring(functions, file);
	lua_pushstring(functions, outputString);
	lua_pushinteger(functions, bOverwrite);
	lua_call(functions, 3, 0); cout << "..................";
}

bool CLuaInterface::GetBoolValue(const char* varName)
{
	lua_getglobal(currentState.second, varName);
	return lua_toboolean(currentState.second, -1);
}

void CLuaInterface::error(const char *errorCode)
{
	if (theErrorState == NULL)
		return;

	lua_getglobal(theErrorState, errorCode);
	const char *errorMsg = lua_tostring(theErrorState, -1);
	if (errorMsg != NULL)
		cout << errorMsg << endl;
	else
		cout << errorCode << "is not valid. \n *** Please contact the developer ***" << endl;
}

void CLuaInterface::Drop()
{
	lua_close(functions);

	//currentState = nullptr;
	map<string, lua_State*>::iterator it = luaStates.begin();
	while (it != luaStates.end())
	{
		lua_close(it->second);
		it = luaStates.erase(it);
	}
}

void CLuaInterface::DropFile(string name)
{
	map<string, lua_State*>::iterator it = luaStates.begin();
	lua_close(it->second);
	luaStates.erase(it);
}

bool CLuaInterface::LoadFile(const string name)
{
	map<string, lua_State*>::iterator it = luaStates.find(name);

	if (it != luaStates.end())
	{
		currentState = (*it);
		return true;
	}

	lua_State *result = lua_open();
	if (result)
	{
		string fileName = "Script//" + name + ".lua";
		// Load lua auxiliary libraries
		luaL_openlibs(result);

		// Load lua script
		if (!luaL_dofile(result, fileName.c_str()))
		{
			std::cout << "Succesfully loaded " << fileName << std::endl;
			currentState = std::pair<string, lua_State*>(name, result);
			luaStates.insert(currentState);
			return true;
		}
		else
		{
			std::cout << "Failed to load " << fileName << std::endl;
			return false;
		}
	}
}

void CLuaInterface::RegisterFunction(string name, int(*luaFunc)(lua_State*))
{
	lua_register(currentState.second, name.c_str(), luaFunc);
}

void CLuaInterface::DoActiveState()
{
	string fileName = "Script//" + currentState.first + ".lua";
	luaL_dofile(currentState.second, fileName.c_str());
}

lua_State* CLuaInterface::GetActiveState()
{
	return currentState.second;
}