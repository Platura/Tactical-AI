#pragma once
#include <unordered_map>
#include <memory>
#include <functional>
#include <string>

template<typename T, typename... P>
class Factory
{
	using create_function = std::function<std::unique_ptr<T>(P const&...)>;

	std::unordered_map<std::string, create_function> m_factory_functions;
public:

	template<typename I>
	void setup(std::string name)
	{
		create_function func(&I::create);
		m_factory_functions.insert({ name, std::move(func)});
	}

	template<typename... U>
	std::unique_ptr<T> createUnique(std::string name, U &&... parameter)
	{
		auto ptr = m_factory_functions.at(name)(std::forward<U>(parameter)...);
		return std::move(ptr);
	}
};

