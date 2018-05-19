#pragma once

#include "LuaManager.h"
#include "ILuaMember.h"
#include <vector>

class LuaFunctionsWrapper
{
private:
	template <class A, class B>
	struct eq {
		static const bool result = false;
	};

	template<class A>
	struct eq<A, A> {
		static const bool result = true;
	};
	////////////////////////////////////////////////
	
	/*template <typename ...Args>
	struct ReturnHolder {
		std::vector<Args...> rets;
	};*/

public:

	template<typename Ret, typename Clazz, typename ...Args>
	inline static int FunctionWrapper2(lua_State * L) {
		const int params = sizeof...(Args);
		Clazz* luaMember = reinterpret_cast<Clazz*>(lua_touserdata(LuaManager::GetCurrentState(), lua_upvalueindex(1)));
		std::string function = LuaManager::GetString(params + 1);

		if (!eq<void, Ret>::result)
		{
			LuaManager::PrintStackSize();
			bool r = ILuaMember::CallMemFuncRet<Ret>(function, LuaManager::get<Args>(LuaManager::GetCurrentState())...);
			LuaManager::push(LuaManager::GetCurrentState(), r);
			
			return 1;
		}

		return 0;
	}

	template<typename Ret, typename Clazz, typename ...Args>
	static void AddCFunction2(Clazz* pPointer) {
		ILuaMember* ptr = dynamic_cast<ILuaMember*>(pPointer);
		if (ptr == nullptr)
			std::cout << "ERROR: wrong class in [" << __func__ << "]" << std::endl;
		else
		{
			lua_pushlightuserdata(LuaManager::GetCurrentState(), pPointer);
			lua_pushcclosure(LuaManager::GetCurrentState(), LuaFunctionsWrapper::FunctionWrapper2<Ret, Clazz, Args...>, 1);
			lua_setglobal(LuaManager::GetCurrentState(), "MemberFunction2");
		}
	}

	

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Clazz, typename Ret, typename ...Arg>
	static void AddCFunction(Clazz* pPointer);

	template<typename Clazz, typename Ret, typename ...Arg>
	static int FunctionWrapper(lua_State * L);
};

template<typename Clazz, typename Ret, typename ...Arg>
inline void LuaFunctionsWrapper::AddCFunction(Clazz * pPointer)
{
	ILuaMember* ptr = dynamic_cast<ILuaMember*>(pPointer);
	if (ptr == nullptr)
		std::cout << "ERROR: wrong class in [" << __func__ << "]" << std::endl;
	else
	{
		lua_pushlightuserdata(LuaManager::GetCurrentState(), pPointer);
		lua_pushcclosure(LuaManager::GetCurrentState(), LuaFunctionsWrapper::FunctionWrapper<Clazz, Ret, Arg...>, 1);
		lua_setglobal(LuaManager::GetCurrentState(), "MemberFunction");
	}
}

template<typename Clazz, typename Ret, typename ...Arg>
inline int LuaFunctionsWrapper::FunctionWrapper(lua_State* L)
{
	//reinterpret_cast
	Clazz* luaMember = reinterpret_cast<Clazz*>(lua_touserdata(LuaManager::GetCurrentState(), lua_upvalueindex(1)));
	int type = LuaManager::GetInteger();
	if (type == 0)
	{
		int arg1 = LuaManager::GetInteger();
		std::string function = LuaManager::GetString();

		/*Ret r = */luaMember->MemberFunction<Ret, Arg...>(function, arg1);
	}
	if (type == 1)
	{
		std::string function = LuaManager::GetString();

		LuaManager::PushInteger(luaMember->MemberFunctionI<Ret, Arg...>(function));
		return 1;
	}
	if (type == 2)
	{
		std::string function = LuaManager::GetString();

		LuaManager::PushFloat(luaMember->MemberFunctionF<Ret, Arg...>(function));
		return 1;
	}
	
	return 0;
}
