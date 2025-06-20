#pragma once
#include "Agent.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <map>
class AgentManager
{
public:
	AgentManager();
	~AgentManager();
	void update(float deltaTime);
	void render(sf::RenderTarget& rt);
	uint32_t addAgent(Agent* nAgent);
	void removeAgent(Agent* rAgent);
	void drawDebug();

	std::vector<uint32_t> getRemovedAgendts(bool clear = true);

	Agent* getAgent(uint32_t id) {
		return m_id_mapping[id];
	}

	bool isAgentActive(uint32_t id) const { return m_id_mapping.at(id) != nullptr;}

	auto begin() {
		return m_agents.begin();
	}

	auto end() {
		return m_agents.end();
	}
protected:
	void internal_delete_Agent(Agent* a);

private:
	uint32_t m_id_counter = 0;
	std::unordered_map<uint32_t, Agent*> m_id_mapping;

	std::vector<Agent*> m_agents;
	bool isAgentUpdating = false;
	std::vector<Agent*> m_agentToBeAdded;
	std::vector<Agent*>m_agentToBeRemoved;

	std::vector<uint32_t> m_removedAgents;
};

