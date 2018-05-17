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
	void MemberFunction(const std::string & pFunction, Arg... arg);

	template<typename Ret, typename ...Arg>
	int MemberFunctionI(const std::string & pFunction);
	template<typename Ret, typename ...Arg>
	float MemberFunctionF(const std::string & pFunction);

	template<typename Ret, typename Clazz, typename ...Args>
	using Function = Ret(Clazz::*)(Args...);

	template<typename Ret, typename Clazz, typename ...Args>
	void AddFunction(std::string pFunction, Clazz*& pClass, Function<Ret, Clazz, Args...>);


	template<typename Ret, typename Clazz, typename ...Args>
	void AddFunctionI(std::string pFunction, Clazz*& pClass, Function<Ret, Clazz, Args...>);
	template<typename Ret, typename Clazz, typename ...Args>
	void AddFunctionF(std::string pFunction, Clazz*& pClass, Function<Ret, Clazz, Args...>);

	template<typename Ret, typename ...Arg>
	void CallFunction(const std::string & pFunction, Arg... arg);

	template<typename Ret, typename ...Arg>
	int CallFunctionI(const std::string & pFunction);
	template<typename Ret, typename ...Arg>
	float CallFunctionF(const std::string & pFunction);

private:
	std::vector<std::string> mFuncNames;
	std::vector<std::string> mFN_INT;
	std::vector<std::string> mFN_FLOAT;
	std::vector<std::function<void(int)>> mFunctions;
	std::vector<std::function<int(void)>> mF_INT;
	std::vector<std::function<float(void)>> mF_FLOAT;
};

template<typename Ret, typename ...Arg>
inline void ILuaMember::MemberFunction(const std::string & pFunction, Arg... arg)
{
	std::cout << "Member Function are being called: " << pFunction << std::endl;

	return CallFunction<Ret, Arg...>(pFunction, arg...);
}

template<typename Ret, typename ...Arg>
inline int ILuaMember::MemberFunctionI(const std::string & pFunction)
{
	std::cout << "Member Function are being called: " << pFunction << std::endl;

	return CallFunctionI<Ret, Arg...>(pFunction);
}

template<typename Ret, typename ...Arg>
inline float ILuaMember::MemberFunctionF(const std::string & pFunction)
{
	std::cout << "Member Function are being called: " << pFunction << std::endl;

	return CallFunctionF<Ret, Arg...>(pFunction);
}

template<typename Ret, typename Clazz, typename ...Args>
inline void ILuaMember::AddFunction(std::string pFunction, Clazz *& pClass, Function<Ret, Clazz, Args...> func)
{
	std::cout << "Added Function [" << pFunction << "]" << std::endl;

	mFuncNames.push_back(pFunction);
	mFunctions.push_back(std::bind(func, pClass, _1));
}

template<typename Ret, typename Clazz, typename ...Args>
inline void ILuaMember::AddFunctionI(std::string pFunction, Clazz *& pClass, Function<Ret, Clazz, Args...> func)
{
	std::cout << "Added Function [" << pFunction << "]" << std::endl;

	mFN_INT.push_back(pFunction);
	mF_INT.push_back(std::bind(func, pClass));
}

template<typename Ret, typename Clazz, typename ...Args>
inline void ILuaMember::AddFunctionF(std::string pFunction, Clazz *& pClass, Function<Ret, Clazz, Args...> func)
{
	std::cout << "Added Function [" << pFunction << "]" << std::endl;

	mFN_FLOAT.push_back(pFunction);
	mF_FLOAT.push_back(std::bind(func, pClass));
}

template<typename Ret, typename ...Arg>
inline void ILuaMember::CallFunction(const std::string & pFunction, Arg... arg)
{
	for (int i = 0; i < mFuncNames.size(); i++)
	{
		if (mFuncNames[i] == pFunction)
		{
			return mFunctions[i](arg...);
		}
	}
}

template<typename Ret, typename ...Arg>
inline int ILuaMember::CallFunctionI(const std::string & pFunction)
{
	for (int i = 0; i < mFN_INT.size(); i++)
	{
		if (mFN_INT[i] == pFunction)
		{
			return mF_INT[i]();
		}
	}
}

template<typename Ret, typename ...Arg>
inline float ILuaMember::CallFunctionF(const std::string & pFunction)
{
	for (int i = 0; i < mFN_FLOAT.size(); i++)
	{
		if (mFN_FLOAT[i] == pFunction)
		{
			return mF_FLOAT[i]();
		}
	}
}
