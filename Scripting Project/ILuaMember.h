#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <functional>

using namespace std::placeholders;

class ILuaMember
{

public:
	ILuaMember();
	~ILuaMember();

	template<typename Ret, typename ...Arg>
	Ret MemberFunction(const std::string & pFunction, Arg... arg);

	template<typename Ret, typename Clazz, typename ...Args>
	using Function = Ret(Clazz::*)(Args...);

	template<typename Ret, typename Clazz, typename ...Args>
	void AddFunction(std::string pFunction, Clazz*& pClass, Function<Ret, Clazz, Args...>);

	template<typename Ret, typename ...Arg>
	Ret CallFunction(const std::string & pFunction, Arg... arg);

private:
	std::vector<std::string> mFuncNames;
	std::vector<std::function<void(int)>> mFunctions;
};

template<typename Ret, typename ...Arg>
inline Ret ILuaMember::MemberFunction(const std::string & pFunction, Arg... arg)
{
	std::cout << "Member Function are being called: " << pFunction << std::endl;

	return CallFunction<Ret, Arg...>(pFunction, arg...);
}

template<typename Ret, typename Clazz, typename ...Args>
inline void ILuaMember::AddFunction(std::string pFunction, Clazz *& pClass, Function<Ret, Clazz, Args...> func)
{
	std::cout << "Test" << std::endl;

	mFuncNames.push_back(pFunction);
	mFunctions.push_back(std::bind(func, pClass, _1));
}

template<typename Ret, typename ...Arg>
inline Ret ILuaMember::CallFunction(const std::string & pFunction, Arg... arg)
{
	for (int i = 0; i < mFuncNames.size(); i++)
	{
		if (mFuncNames[i] == pFunction)
		{
			return mFunctions[i](arg...);
		}
	}
}
