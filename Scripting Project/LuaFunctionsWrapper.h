#pragma once

#include "LuaManager.h"
#include "ILuaMember.h"

class LuaFunctionsWrapper
{
public:
	LuaFunctionsWrapper();
	~LuaFunctionsWrapper();

	template<typename Clazz, typename Ret, typename ...Arg>
	static void AddCFunction(Clazz* pPointer);

	template<typename Clazz, typename Ret, typename ...Arg>
	static int FunctionWrapper(lua_State * L);

private:
	/*template <std::size_t n, typename = std::make_index_sequence<n>>
	struct nth_element_impl;

	template <std::size_t n, std::size_t ...ignore>
	struct nth_element_impl<n, std::index_sequence<ignore...>> {
		template <typename Tn>
		static Tn f(decltype((void*)ignore)..., Tn*, ...);
	};

	template <typename T>
	struct wrapper { using type = T; };

	template <std::size_t n, typename ...T>
	using nth_element = typename decltype(
		nth_element_impl<n>::f(static_cast<wrapper<T>*>(0)...)
		)::type;*/
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
