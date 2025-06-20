#pragma once
#include <unordered_map>
#include "Blackboard.h"


class BlackboardManager
{
private:
	Blackboard m_global;
	std::unordered_map<aiTeamId, Blackboard> m_team_blackboard;
	std::unordered_map<aiAgentId, Blackboard> m_agent_blackboard;

	std::vector<aiAgentId> m_agents;
	std::unordered_map<aiTeamId, std::vector<aiAgentId>> m_teams;
public:
	Blackboard& getGlobal() {
		return m_global;
	}

	Blackboard& getTeamBlackboard(aiTeamId id)
	{
		return m_team_blackboard[id];
	}

	Blackboard& getAgentBlackboard(aiAgentId id)
	{
		return m_agent_blackboard[id];
	}

	void createAgentBlackboard(aiAgentId a, aiTeamId t)
	{
		m_agent_blackboard.insert({ a, Blackboard{} });
		m_agents.push_back(a);
		m_teams[t].push_back(a);
	}

	std::vector<aiAgentId> const& getAgents() const {
		return m_agents;
	}

	std::vector<aiAgentId> const& getAgents(aiTeamId team) const {
		return m_teams.at(team);
	}

	aiTeamId getTeam(aiAgentId a) const {
		auto t_ptr = std::find_if(m_teams.begin(), m_teams.end(), [a](std::pair< aiTeamId, std::vector<aiAgentId>> const& data) {
			return std::find(data.second.begin(), data.second.end(), a) != data.second.end();
			});

		return t_ptr != m_teams.end() ? t_ptr->first : 0;
	}
	auto const& getTeams() const { return m_teams;  }


	void removeAgent(aiAgentId id);
};

