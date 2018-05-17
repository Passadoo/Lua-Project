#pragma once

#include <map>
#include <string>
#include <functional>
#include <memory>

/*class FunctionTypes
{
public:
	struct Func_t {
		virtual ~Func_t() = default;
	};
	using callbacks_t = std::map<std::string, std::unique_ptr<Func_t>>;
	callbacks_t callbacks;

	// Ret(Clazz::*)(Args...);
	template<typename Clazz, typename ...A>
	struct Cb_t : public Func_t {
		using cb = std::function<void(Clazz::*)(A...)>;
		cb callback;
		Cb_t(cb p_callback) : callback(p_callback) {}
	};
	
	template<typename ...A>
	void call(std::string str, A&& ... args)
	{
		using func_t = Cb_t<A...>;
		using cb_t = std::function<void(A...)>;
		const Func_t& base = *callbacks[str];
		const cb_t& fun = static_cast<const func_t&>(base).callback;
		fun(std::forward<A>(args)...);
	}
};*/

struct ICaller {};

#define FUNC void (Clazz::*)(Args...)

class UserRendererMultiArgs : public ICaller {
public:
	UserRendererMultiArgs(int, int) {}
	~UserRendererMultiArgs() {}
	static ICaller *Create(int i1, int i2) {
		return new UserRendererMultiArgs(i1, i2);
	}
};

template <typename... Args>
struct MapHolder {
	static std::map<std::string, std::function<void(Args...)>> CallbackMap;
};

template <typename... Args>
std::map<std::string, std::function<void(Args...)>> MapHolder<Args...>::CallbackMap;

class CallFactory {
public:
	template<typename Ret, typename Clazz, typename ...Args, typename ...T>
	static void RegisterCaller(std::string name, Clazz*& pClass, Ret(Clazz::*Callback)(Args...), T... p) {
		MapHolder<Args...>::CallbackMap[name] = std::bind(Callback, pClass, p...);
	}

	template <typename... Args>
	static void CallFunction(const std::string &name, Args &&... args) {
		MapHolder<Args...>::CallbackMap[name](std::forward<Args>(args)...);
	}
};