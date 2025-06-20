#include "SelectFollowAction.h"

void SelectFollowAction::onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput*)
{
	auto agent_pos = bm.getAgentBlackboard(m_agent).getValue<aiPosition>("position");
	auto ids = bm.getAgents(m_team);
	std::vector<std::pair<aiAgentId, float>> front_candidates;
	for (int i = 0; i < ids.size(); ++i)
	{
		auto is_front = bm.getAgentBlackboard(ids.at(i)).getValue<aiInt>("agent_type");
		if (!is_front.has_value() || is_front.value() != 1)
		{
			continue;
		}
		auto front_pos = bm.getAgentBlackboard(ids.at(i)).getValue<aiPosition>("position");

		float dx = agent_pos.value().x - front_pos.value().x;
		float dy = agent_pos.value().y - front_pos.value().y;
		float distance = std::sqrt(dx * dx + dy * dy);

		front_candidates.emplace_back(ids.at(i), distance);
	}
	std::sort(front_candidates.begin(), front_candidates.end(), [](auto& a, auto& b) {
		return a.second < b.second;
		});

	// Randomly select one of the closest N front agents
	int num_candidates = std::min(3, static_cast<int>(front_candidates.size()));
	if (num_candidates > 0)
	{
		int random_index = std::rand() % num_candidates;
		selected_front = front_candidates[random_index].first;
	}

}

void SelectFollowAction::onActionUpdate(BlackboardManager& bm, IEngineDataOutput*)
{
	m_isFinished = true;
}

void SelectFollowAction::onActionFinished(BlackboardManager& bm, IEngineDataOutput*)
{
	*m_front_agent.getPtr<aiAgentId>(bm) = selected_front;
}

std::unique_ptr<IAction> SelectFollowAction::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<SelectFollowAction>();

	if (parameter.contains("front_agent"))
	{
		result->m_front_agent.init(agent, team, parameter["front_agent"]);
	}

	return result;
}
