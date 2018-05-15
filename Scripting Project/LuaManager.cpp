#include "LuaManager.h"

// PE = Print Error
#define PE_LUA_TOP(type) std::cout << "ERROR: not a " << typeid(type).name() << " on top of the stack [" << __func__ << "]" << std::endl;

#define LUA_GETTOP(var){\
	if (!lua_is##var(mL, -1))\
		PE_LUA_TOP(var);\
	var = lua_to##var(mL, -1);\
	lua_pop(mL, 1);\
	return var;\
}\

lua_State * LuaManager::mL = nullptr;
std::vector<std::string> LuaManager::mMetaTables;

LuaManager::LuaManager()
{
}

LuaManager::~LuaManager()
{
}

void LuaManager::InitLuaManager()
{
	mL = luaL_newstate();
	luaL_openlibs(mL);
}

void LuaManager::CloseLuaManager()
{
	lua_close(mL);
}

void LuaManager::LoadScript(const std::string & pPath)
{
	int error = luaL_loadfile(mL, pPath.c_str()) || lua_pcall(mL, 0, 0, 0);
	if (error)
	{
		std::cout << "ERROR: could not load lua script [" << pPath << "]" << std::endl;
		lua_pop(mL, 1);
		PrintStackSize();
	}
	else
	{
		std::cout << "[" << pPath << "] Script loaded successfully" << std::endl;
	}
}

void LuaManager::CallLuaFunction(const std::string & pFuncName)
{
	lua_getglobal(mL, pFuncName.c_str());
	CallLuaFunction(pFuncName, 0, 0);
}

void LuaManager::CallLuaFunction(const std::string & pFuncName, int pArg, int pResults)
{
	if (pArg == 0 && pResults != 0)
		lua_getglobal(mL, pFuncName.c_str());
	int error = lua_pcall(mL, pArg, pResults, 0);
	if (error)
	{
		std::cout << "ERROR: could not call function: [" << pFuncName << "]" << std::endl;
		lua_pop(mL, 1);
		PrintStackSize();
	}
}

lua_State * LuaManager::GetCurrentState()
{
	return mL;
}

void LuaManager::PushInteger(int pInteger)
{
	lua_pushinteger(mL, pInteger);
}

void LuaManager::PushFloat(float pFloat)
{
	lua_pushnumber(mL, pFloat);
}

void LuaManager::PushString(std::string pString)
{
	lua_pushstring(mL, pString.c_str());
}

void LuaManager::PushBool(bool pBool)
{
	lua_pushboolean(mL, pBool);
}

int LuaManager::GetInteger()
{
	int integer;
	LUA_GETTOP(integer);
	return integer;
}

float LuaManager::GetFloat()
{
	float number;
	LUA_GETTOP(number);
	return number;
}

std::string LuaManager::GetString()
{
	std::string string;
	LUA_GETTOP(string);
	return string;
}

bool LuaManager::GetBool()
{
	bool boolean;
	LUA_GETTOP(boolean);
	return boolean;
}

std::string LuaManager::GetMetaTable(const std::string & pObjectName)
{
	return "Meta" + pObjectName;
}

std::string LuaManager::GetMetaTableAndCheck(const std::string & pObjectName)
{
	std::string ret = "";
	for (std::string str : mMetaTables)
	{
		if (str.find(pObjectName) != std::string::npos)
		{
			ret = str;
		}
	}
	return ret;
}

void LuaManager::RegisterObjectFunctions(const std::string & pObjectName, luaL_Reg sMonsterRegs[])
{
	std::string metatable = "Meta" + pObjectName;
	if (luaL_newmetatable(mL, metatable.c_str()) == 0)
		std::cout << "ERROR: metatable with name [" << metatable << "] already exists" << std::endl;
	else
	{
		mMetaTables.push_back(metatable);
		luaL_setfuncs(mL, sMonsterRegs, 0);
		lua_pushvalue(mL, -1);
		lua_setfield(mL, -1, "__index");
		lua_setglobal(mL, pObjectName.c_str());
	}
}

void LuaManager::PrintStackSize()
{
	std::cout << "Size of Lua stack: " << lua_gettop(mL) << std::endl;
}
