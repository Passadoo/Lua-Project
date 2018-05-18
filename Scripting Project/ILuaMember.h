#pragma once

#include <map>
#include <string>
#include <vector>
#include <iostream>

#include <functional>

using namespace std::placeholders;

#define ILuaMember_CALL_ERROR(ret, args, retV)\
if (MapHolder<ret, args>::CallbackMap.find(name) == MapHolder<ret, args>::CallbackMap.end())\
{\
	std::cout << "Function [" << name << "] is not a registered function" << std::endl;\
	return retV;\
}\

#define CALL_RET_ERROR(ret, args) ILuaMember_CALL_ERROR(ret, args, ret())
#define CALL_VOID_ERROR(args) ILuaMember_CALL_ERROR(void, args, )

class ILuaMember
{
private:
	/*template <class A, class B>
	struct eq {
		static const bool result = false;
	};

	template<class A>
	struct eq<A, A> {
		static const bool result = true;
	};*/

	template <typename Ret, typename... Args>
	struct MapHolder {
		static std::map<std::string, std::function<Ret(Args...)>> CallbackMap;
	};

public:

	template<typename Ret, typename Clazz, typename ...Args, typename ...T>
	static void RegisterCaller(std::string name, Clazz*& pClass, Ret(Clazz::*Callback)(Args...), T... p) {
		const int params = sizeof...(Args);
		ILuaMember* luaMember = dynamic_cast<ILuaMember*>(pClass);
		if (!luaMember)
		{
			std::cout << "Class of function [" << name << "] is not a Lua member" << std::endl;
			return;
		}
		std::cout << "Register function [" << name << "] with [" << params << "] nr of arguments" << std::endl;
		MapHolder<Ret, Args...>::CallbackMap[name] = std::bind(Callback, pClass, p...);
	}

	template <typename... Args>
	static void CallFunc(const std::string &name, Args &&... args) {
		CALL_VOID_ERROR(Args...)
		std::cout << "Called function [" << name << "]" << std::endl;
		MapHolder<void, Args...>::CallbackMap[name](std::forward<Args>(args)...);
	}

	template <typename Ret, typename... Args>
	static Ret CallFuncRet(const std::string &name, Args &&... args) {
		CALL_RET_ERROR(Ret, Args...)
		std::cout << "Called function [" << name << "]" << std::endl;
		return MapHolder<Ret, Args...>::CallbackMap[name](std::forward<Args>(args)...);
	}
};

template <typename Ret, typename... Args>
std::map<std::string, std::function<Ret(Args...)>> ILuaMember::MapHolder<Ret, Args...>::CallbackMap;