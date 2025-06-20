#include "BlackboardManager.h"

void BlackboardManager::removeAgent(aiAgentId id)
{
	m_agents.erase(std::remove(m_agents.begin(), m_agents.end(), id), m_agents.end());

	for (auto& [team, agents] : m_teams)
	{
		agents.erase(std::remove(agents.begin(), agents.end(), id), agents.end());

	}

	// TODO: Delete blackboard
	m_agent_blackboard.erase(id);
}
