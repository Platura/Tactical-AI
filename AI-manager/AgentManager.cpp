#include "AgentManager.h"
#include "imgui.h"
#include <fmt/format.h>
#include <algorithm>
#include <vector>

AgentManager::AgentManager()
{
}

AgentManager::~AgentManager()
{
	for (auto el : m_agents)
	{
		delete el;
	}
}

void AgentManager::update(float deltaTime)
{
	isAgentUpdating = true;
	for (auto& el : m_agents)
	{
		el->update(deltaTime, this);
	}
	isAgentUpdating = false;
	if (!m_agentToBeAdded.empty())
	{
		m_agents.insert(m_agents.end(), m_agentToBeAdded.begin(), m_agentToBeAdded.end());
		m_agentToBeAdded.clear();
	}
	if (!m_agentToBeRemoved.empty())
	{
		/*
		for (auto el : m_agentToBeRemoved)
		{
			if (el != nullptr)
			{
				delete el;
				el = nullptr;
			}
		}
		m_agents.erase(std::remove_if(m_agents.begin(), m_agents.end(), [&](Agent* el) {
			return std::find(m_agentToBeRemoved.begin(), m_agentToBeRemoved.end(), el) != m_agentToBeRemoved.end(); 
			}), m_agents.end());
			*/
		for (auto el : m_agentToBeRemoved)
		{
			internal_delete_Agent(el);
		}
		m_agentToBeRemoved.clear();
	}
}

void AgentManager::render(sf::RenderTarget& rt)
{
	for (auto& el : m_agents)
	{
		el->render(rt);
	}
}

uint32_t AgentManager::addAgent(Agent* nAgent)
{
	nAgent->setId(++m_id_counter);
	m_id_mapping[nAgent->getId()] = nAgent;
	if (isAgentUpdating)
	{
		m_agentToBeAdded.push_back(nAgent);
	}
	else
	{
		m_agents.push_back(nAgent);
	}
	return m_id_counter;
}

void AgentManager::removeAgent(Agent* rAgent)
{
	if (isAgentUpdating)
	{
		m_agentToBeRemoved.push_back(rAgent);
	}
	else
	{
		internal_delete_Agent(rAgent);
	}
}


void AgentManager::drawDebug()
{
	std::vector<Agent*> to_delete;
	ImGui::Begin("DebugManager");
	for (auto el : m_agents) 
	{
		std::string name = fmt::format("Agent {}", (void*)el);
		bool not_delete_agent = true;

		if(ImGui::CollapsingHeader((*el).getName().c_str(), &not_delete_agent))
		{
			ImGui::PushID(el);
			el->drawDebug();
			ImGui::PopID();
		}

		if (!not_delete_agent)
		{
			to_delete.push_back(el);
		}
	}

	for (auto erase : to_delete)
	{
		auto it = std::find(m_agents.begin(), m_agents.end(), erase);
		if (it == m_agents.end())
		{
			continue;
		}

		m_agents.erase(it);
	}
	
	ImGui::End();
}

std::vector<uint32_t> AgentManager::getRemovedAgendts(bool clear )
{
	if(clear)
	{
		return std::move(m_removedAgents);
	}
	else{
		return (m_removedAgents);
	}
}

void AgentManager::internal_delete_Agent(Agent* rAgent)
{
	auto const id = rAgent->getId();

	delete rAgent;
	m_agents.erase(std::remove(m_agents.begin(), m_agents.end(), rAgent), m_agents.end());

	m_id_mapping[id] = nullptr;

	m_removedAgents.push_back(id);
	//auto it = std::find(m_id_mapping.begin(), m_id_mapping.end(), [rAgent](auto pair) {return pair.second == rAgent; });
	//m_id_mapping.erase(it);

}
