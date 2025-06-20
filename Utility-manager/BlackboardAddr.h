#pragma once
#include "BlackboardManager.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class BlackboardAddr
{
	std::string m_key;
	uint32_t m_index; // Agent or team index

	enum class Type
	{
		AGENT,
		TEAM,
		GLOBAL,
		NONE
	} m_type = Type::NONE;


public:
	void init(aiAgentId agent, aiTeamId team, json const& value_config)
	{
		if (value_config.is_string())
		{
			auto name = value_config.get<std::string>();

			auto dot = std::find(name.begin(), name.end(), '.');

			if (dot == name.end())
			{
				m_type = Type::AGENT;
				m_key = name;
				m_index = agent;
				return;
			}

			auto blackboard_type = std::string{ name.begin(), dot };
			auto key = std::string{ dot + 1, name.end() };

			if (blackboard_type == "self")
			{
				m_type = Type::AGENT;
				m_key = key;
				m_index = agent;
			}
			else if (blackboard_type == "team")
			{
				m_type = Type::TEAM;
				m_key = key;
				m_index = team;
			}
			else if (blackboard_type == "global")
			{
				m_type = Type::GLOBAL;
				m_key = key;
			}
		}
	}

	Blackboard& getBlackboard(BlackboardManager& bm)
	{
		if (m_type == Type::AGENT)
			return bm.getAgentBlackboard(m_index);
		else if (m_type == Type::TEAM)
			return bm.getTeamBlackboard(m_index);
		else
			return bm.getGlobal();
	}

	template<typename T>
	T* getPtr(BlackboardManager& bm)
	{
		if (m_type == Type::NONE)
			return {};
		return getBlackboard(bm).getValuePtr<T>(m_key);
	}

	auto& getVariant(BlackboardManager& bm)
	{
		return getBlackboard(bm).get(m_key);
	}
};
