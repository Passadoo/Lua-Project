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

	template<typename Ret, typename... Args>
	struct Func {
		template<typename Ret, typename... Args> struct Function {
			static void PushToStack(const std::string &name) {
				LuaManager::push<Ret>(LuaManager::GetCurrentState(), ILuaMember::CallMemFunc<Ret>(name, LuaManager::get<Args>(LuaManager::GetCurrentState())...));
			}
		};
		template<> struct Function<void, Args...> {
			static void PushToStack(const std::string &name) {
				ILuaMember::CallMemFunc<Ret>(name, LuaManager::get<Args>(LuaManager::GetCurrentState())...);
			}
		};
	};

	template <typename Ret, typename... Args>
	static void PushToStack(const std::string &name) {
		Func<Ret, Args...>::Function<Ret, Args...>::PushToStack(name);
	}

public:

	template<typename Clazz, typename Ret, typename ...Args>
	inline static int FunctionWrapper2(lua_State * L) {
		const int params = sizeof...(Args);
		Clazz* luaMember = reinterpret_cast<Clazz*>(lua_touserdata(LuaManager::GetCurrentState(), lua_upvalueindex(1)));
		std::string function = LuaManager::GetString(params + 1);

		PushToStack<Ret, Args...>(function);
		if (!eq<void, Ret>::result)
			return 1;
		return 0;
	}

	template<typename Clazz, typename Ret, typename ...Args>
	static void AddCFunction2(Clazz* pPointer, std::string luafuncname) {
		ILuaMember* ptr = dynamic_cast<ILuaMember*>(pPointer);
		if (ptr == nullptr)
			std::cout << "ERROR: wrong class in [" << __func__ << "]" << std::endl;
		else
		{
			lua_pushlightuserdata(LuaManager::GetCurrentState(), pPointer);
			std::cout << "args: " << sizeof...(Args) << std::endl;
			lua_pushcclosure(LuaManager::GetCurrentState(), LuaFunctionsWrapper::FunctionWrapper2<Clazz, Ret, Args...>, 1);
			lua_setglobal(LuaManager::GetCurrentState(), luafuncname.c_str());
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
