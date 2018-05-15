#pragma once

#include <lua.hpp>
#include "lua.hpp"

#include <string>
#include <iostream>
#include "Defined.h"
#include <vector>

class LuaManager
{
public:
	LuaManager();
	~LuaManager();

	void LoadScript(const std::string & pPath);
	void CallLuaFunction(const std::string & pFuncName);
	void CallLuaFunction(const std::string & pFuncName, int pArg, int pResults);

	lua_State * GetCurrentState() const;

	int GetInteger();
	float GetFloat();
	std::string GetString();
	bool GetBool();

	/* C++ functions */
	// Need to be called before the script that has the functions is loaded
	void RegisterObjectFunctions(const std::string & pObjectName, luaL_Reg sMonsterRegs[]);

private:
	lua_State * mL = nullptr;
	std::vector<std::string> mMetaTables;
private:
	void initLua();
	void printStackSize(lua_State *& pL) const;
};
