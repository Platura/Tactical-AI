#pragma once
#include <unordered_map>
#include <string>
#include <variant>
#include <optional>
#include <nlohmann/json.hpp>
#include "Types.hpp"
#include "InfluenceMap.h"
#include "TacticalMap.h"
#include "Costfield.h"

using json = nlohmann::json;

struct aiNone{};

using values = std::variant<aiNone, aiInt, aiUInt, aiFloat, aiPosition, uint64_t, std::vector<std::pair<uint32_t, uint32_t>>, InfluenceMap, TacticalMap, Costfield, std::vector<aiAgentId>>;

values valuesFromJson(json const& j);

class Blackboard
{
	std::unordered_map<std::string, values> m_data;

	values m_none_value = aiNone{};
public:

	values& get(std::string const& key)
	{
		auto it = m_data.find(key);

		if (it == m_data.end())
		{
			return m_none_value;
		}
		return it->second;
		
	}

	template<typename T>
	void createField(std::string const& key)
	{
		m_data.insert({ key, values{T{}} });

		if constexpr (std::is_same_v<T, TacticalMap>)
		{
			TacticalMap* it = std::get_if<TacticalMap>(&m_data[key]);
			registerTacticalMap(it, key);
		}
	}

	template<typename T>
	std::optional<T> getValue(std::string const& key)
	{
		auto it = m_data.find(key);

		if (it == m_data.end())
		{
			//createField<T>(key);
			//it = m_data.find(key);
			return { };
		}
		

		auto ptr = std::get_if<T>(&it->second);

		if (ptr == nullptr)
		{
			return {};
		}
		else
		{
			return *ptr;
		}
	}

	template<typename T>
	T* getValuePtr(std::string const& key)
	{
		auto it = m_data.find(key);

		if (it == m_data.end())
		{
			createField<T>(key);
			it = m_data.find(key);
		}


		auto ptr = std::get_if<T>(&it->second);

		if (ptr == nullptr)
		{
			return nullptr;
		}
		else
		{
			return ptr;
		}
	}

	template<typename T>
	T* getValuePtrOr(std::string const& key, T* other = nullptr)
	{
		auto it = m_data.find(key);

		if (it == m_data.end())
		{
			return other;
		}


		auto ptr = std::get_if<T>(&it->second);

		if (ptr == nullptr)
		{
			return other;
		}
		else
		{
			return ptr;
		}
	}

	template<typename T>
	void setValue(std::string const& key, T&& value)
	{
		m_data.insert_or_assign(key, value);
	}

	void removeValue(std::string const& key)
	{
		m_data.erase(key);
	}

	void drawDebug();
	void registerTacticalMap(TacticalMap* t, std::string key);
};

