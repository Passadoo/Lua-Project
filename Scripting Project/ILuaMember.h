#pragma once

#include <map>
#include <string>
#include <vector>
#include <iostream>

#include <functional>

using namespace std::placeholders;

template <typename... Args>
struct MapHolder {
	static std::map<std::string, std::function<void(Args...)>> CallbackMap;
};

template <typename... Args>
std::map<std::string, std::function<void(Args...)>> MapHolder<Args...>::CallbackMap;

class ILuaMember
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

public:
	ILuaMember();
	~ILuaMember();

	template<typename Ret, typename Clazz, typename ...Args, typename ...T>
	static void RegisterCaller(std::string name, Clazz*& pClass, Ret(Clazz::*Callback)(Args...), T... p) {
		MapHolder<Args...>::CallbackMap[name] = std::bind(Callback, pClass, p...);
	}

	template <typename... Args>
	static void CallFunctionMap(const std::string &name, Args &&... args) {
		MapHolder<Args...>::CallbackMap[name](std::forward<Args>(args)...);
	}
	/////////////////////////////

	template<typename Ret, typename ...Arg>
	inline Ret MemberFunction2(const std::string & pFunction, Arg && ... arg) {

		std::cout << "Member Function are being called: " << pFunction << std::endl;

		return CallFunction2<Ret, Arg...>(pFunction, arg...);
	};

	template<class Ret, typename ...Arg>
	inline void CallFunction2(Ret& ret, const std::string & pFunction, Arg && ... arg) {
		for (int i = 0; i < mFuncNames.size(); i++)
		{
			if (mFuncNames[i] == pFunction)
			{
				//if (eq<Ret, void>::result)
				//	return mFunctions[i](arg...);
				//else if (eq<Ret, int>::result)
				ret = mF_Int_INT[i](arg...);
			}
		}
	};
	template<typename ...Arg>
	inline void CallFunction2(const std::string & pFunction, Arg && ... arg) {
		CallFactory::CallFunction(pFunction, arg...);
		/*for (int i = 0; i < mFuncNames.size(); i++)
		{
			if (mFuncNames[i] == pFunction)
			{
				mFunctions[i](arg...);
			}
		}*/
	};

	template<typename Ret, typename Clazz, typename ...Args>
	using FunctionArgs = Ret(Clazz::*)(Args...);
	template<typename Ret, typename Clazz>
	using FunctionVoid = Ret(Clazz::*)();

	template<typename Ret, typename Clazz, typename ...Args, typename ...T>
	void AddFunction2(std::string pFunction, Clazz*& pClass, FunctionArgs<Ret, Clazz, Args...> func, T... p) {
		const int params = sizeof...(Args);
		
		std::cout << "Added Function [" << pFunction << "] with [" << params << "] nr of arguments" << std::endl;

		//mFuncNames.push_back(pFunction);
		//not used: mFunctions.push_back([pClass](Args... args) { func(args...); });
		//mFunctions.push_back(std::bind(func, pClass, p...));
		CallFactory::RegisterCaller(pFunction, pClass, func, p...);
	};

	///////////////////////////////////////////////////////////////

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
	std::vector<std::function<int(int)>> mF_Int_INT;
};

/////////////////////////////////////////////////////////////////////////////////

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
