#pragma once

#include <lua.hpp>
#include "lua.hpp"

#include <string>
#include <iostream>
#include "Defined.h"
#include <vector>
#include "ILuaMember.h"
#include <sstream>

#include <typeinfo>

class LuaManager
{
private:
	/*template <typename Arg>
	inline static void _push(lua_State * pL, Arg arg) {
		std::cout << "ERROR: Could not push [" << arg << "] of type [" << typeid(arg).name() << "] to the stack" << std::endl;
		return;
	}
	template <>
	inline static void _push<int>(lua_State * pL, int arg) {
		std::cout << "pus_int: " << arg << std::endl;
		LuaManager::PushInteger(pL, arg);
	}
	template <>
	inline static void _push<bool>(lua_State * pL, bool arg) {
		LuaManager::PushBool(pL, arg);
	}
	template <>
	inline static void _push<std::string>(lua_State * pL, std::string arg) {
		LuaManager::PushString(pL, arg);
	}
	template <>
	inline static void _push<float>(lua_State * pL, float arg) {
		LuaManager::PushFloat(pL, arg);
	}*/
	inline static void _push(lua_State * pL, ILuaMember* arg) {
		ILuaMember** ptr = reinterpret_cast<ILuaMember**>(lua_newuserdata(LuaManager::GetCurrentState(), sizeof(ILuaMember*)));
		*ptr = arg;
		luaL_getmetatable(LuaManager::GetCurrentState(), LuaManager::GetMetaTable(arg->GetLuaObject()).c_str());
		lua_setmetatable(LuaManager::GetCurrentState(), -2);
	}
	inline static void _push(lua_State * pL, int arg) {
		LuaManager::PushInteger(pL, arg);
	}
	inline static void _push(lua_State * pL, bool arg) {
		LuaManager::PushBool(pL, arg);
	}
	inline static void _push(lua_State * pL, std::string arg) {
		LuaManager::PushString(pL, arg);
	}
	inline static void _push(lua_State * pL, float arg) {
		LuaManager::PushFloat(pL, arg);
	}

	template <typename Ret>
	inline static Ret _get(lua_State * pL) {
		return 0;
	}

	template <>
	inline static int _get<int>(lua_State * pL) {
		return LuaManager::GetInteger(pL);
	}
	template <>
	inline static bool _get<bool>(lua_State * pL) {
		return LuaManager::GetBool(pL);
	}
	template <>
	inline static std::string _get<std::string>(lua_State * pL) {
		return LuaManager::GetString(pL);
	}
	template <>
	inline static float _get<float>(lua_State * pL) {
		return LuaManager::GetFloat(pL);
	}

public:
	// Push values to lua
	template <typename Arg>
	static void push(lua_State * L, Arg&& arg) {
		//return _push<Arg>(L, std::forward<Arg>(arg));
		return _push(L, std::forward<Arg>(arg));
	}
	
	template <typename... Args>
	static void push_all(lua_State * L, Args&&... args) {
		std::initializer_list<int>{(push<Args>(L, std::forward<Args>(args)), 0)...};
	}

	// Get values from lua
	template <typename Ret>
	static Ret get(lua_State * L) {
		return _get<Ret>(L);
	}
	
	template<typename Ret, typename... Args>
	struct Func {
		template<typename Ret, typename... Args> struct Function {
			static Ret CallLuaFunc(const std::string & pFuncName, int r, Args && ... args) {
				const int params = sizeof...(args);
				lua_getglobal(LuaManager::GetCurrentState(), pFuncName.c_str());
				push_all(LuaManager::GetCurrentState(), std::forward<Args>(args)...);
				if (params == 0)
					lua_pop(LuaManager::GetCurrentState(), -1);
				if (r == 0)
					r = 1;
				LuaManager::CallLuaFunction(pFuncName, params, r);
				return get<Ret>(LuaManager::GetCurrentState());
			}
		};
		template<> struct Function<void, Args...> {
			static void CallLuaFunc(const std::string & pFuncName, int r, Args&& ... args) {
				const int params = sizeof...(args);
				lua_getglobal(LuaManager::GetCurrentState(), pFuncName.c_str());
				push_all(LuaManager::GetCurrentState(), std::forward<Args>(args)...);
				LuaManager::CallLuaFunction(pFuncName, params, r);
			}
		};
	};

	// If the lua function returns more than one values
	template <typename Ret, typename... Args>
	static Ret CallLuaFuncS(const std::string & pFuncName, int r, Args&& ... args) {
		return Func<Ret, Args...>::Function<Ret, Args...>::CallLuaFunc(pFuncName, r, std::forward<Args>(args)...);
	}

	// If the lua function returns one or none values
	template <typename Ret, typename... Args>
	static Ret CallLuaFunc(const std::string & pFuncName, Args&& ... args) {
		return Func<Ret, Args...>::Function<Ret, Args...>::CallLuaFunc(pFuncName, 0, std::forward<Args>(args)...);
	}

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


	static void PushInteger(lua_State *& pL, int pInteger);
	static void PushFloat(lua_State *& pL, float pFloat);
	static void PushString(lua_State *& pL, std::string pString);
	static void PushBool(lua_State *& pL, bool pBool);

	static int GetInteger();
	static float GetFloat();
	static std::string GetString();
	static bool GetBool();

	static int GetInteger(lua_State *& pL);
	static float GetFloat(lua_State *& pL);
	static std::string GetString(lua_State *& pL);
	static bool GetBool(lua_State *& pL);

	static int GetInteger(int params);
	static float GetFloat(int params);
	static std::string GetString(int params);
	static bool GetBool(int params);

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
