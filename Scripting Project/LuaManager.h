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

	static void InitLuaManager();
	static void CloseLuaManager();

	static void LoadScript(const std::string & pPath);
	static void CallLuaFunction(const std::string & pFuncName);
	static void CallLuaFunction(const std::string & pFuncName, int pArg, int pResults);

	static lua_State * GetCurrentState();

	static void PushInteger(int pInteger);
	static void PushFloat(float pFloat);
	static void PushString(std::string pString);
	static void PushBool(bool pBool);

	static int GetInteger();
	static float GetFloat();
	static std::string GetString();
	static bool GetBool();

	static std::string GetMetaTable(const std::string & pObjectName);
	static std::string GetMetaTableAndCheck(const std::string & pObjectName);

	static void PrintStackSize();

	/* C++ functions */
	// Need to be called before the script that has the functions is loaded
	static void RegisterObjectFunctions(const std::string & pObjectName, luaL_Reg sMonsterRegs[]);

	/* complementary functions for C++ functions in Lua */
	// Retrun nullptr if <T> not exists
	template<typename T>
	static T* GetObjectPtr(const std::string & pObjectName, int pIndex = 1);
	template<typename T>
	static T* GetObjectPtrEmpty(const std::string & pLuaObjectName, const std::string & pObjectName, int pIndex = 1);

private:
	static lua_State * mL;
	static std::vector<std::string> mMetaTables;

};

template<typename T>
inline T * LuaManager::GetObjectPtr(const std::string & pObjectName, int pIndex)
{
	T* objectPtr = nullptr;

	void* ptr = luaL_testudata(mL, pIndex, GetMetaTable(pObjectName).c_str());
	if (ptr != nullptr)
		objectPtr = *(T**)ptr;

	return objectPtr;
}

template<typename T>
inline T * LuaManager::GetObjectPtrEmpty(const std::string & pLuaObjectName, const std::string & pObjectName, int pIndex)
{
	lua_getglobal(mL, pLuaObjectName.c_str());
	T* ptr = LuaManager::GetObjectPtr<Enemy>(pObjectName.c_str());
	lua_pop(mL, -1);
	return ptr;
}
