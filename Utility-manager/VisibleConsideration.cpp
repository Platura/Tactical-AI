#include "VisibleConsideration.h"

VisibleConsideration::VisibleConsideration()
{
}

float VisibleConsideration::compute(BlackboardManager& bm)
{
    auto agent_vis = bm.getAgentBlackboard(m_agent).getValue<TacticalMap>("agent_vis");
	auto agent_pos = bm.getAgentBlackboard(m_agent).getValue<aiPosition>("position").value();
	std::vector<int> nearest_ids;
	int min_distance = 200;
	auto target_ids = bm.getAgents(m_target_team);
	for (int i = 0; i < target_ids.size(); ++i)
	{
		auto target_pos = bm.getAgentBlackboard(target_ids.at(i)).getValue<aiPosition>("position");
		if (m_agent == target_ids.at(i))
			continue;
		if (!target_pos.has_value())
			continue;
		Vec2D direction{ target_pos.value().x - agent_pos.x, target_pos.value().y - agent_pos.y };
		auto distance = sqrt(direction.x * direction.x + direction.y * direction.y);

		if (distance <= min_distance)
		{
			nearest_ids.push_back(target_ids.at(i));
		}
	}
	//if no one close 
	if (nearest_ids.empty())
	{
		return 0.f;
	}
	std::vector<aiAgentId> half_visible;
	std::vector<aiAgentId> visible;
	for (int j = 0; j < nearest_ids.size();++j)
	{
		auto close_position = bm.getAgentBlackboard(nearest_ids.at(j)).getValue<aiPosition>("position");
		if (!agent_vis.has_value())
			continue;
		if (agent_vis.value().at(close_position.value().x/32, close_position.value().y/32) == 0)
			continue;
		float vis_val = agent_vis.value().at(close_position.value().x / 32, close_position.value().y / 32);
		if (vis_val > 0 && vis_val < 1)
		{
			half_visible.push_back(nearest_ids.at(j));
			continue;
		}
		visible.push_back(nearest_ids.at(j));
	}

	//if there are visible enemies
	if (visible.size()>0)
	{	
		bm.getAgentBlackboard(m_agent).setValue("agent_target", visible.at(0));
		return 1.f;
	}
}

std::unique_ptr<IConsideration> VisibleConsideration::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
    auto result = std::make_unique<VisibleConsideration>();
	if (parameter.contains("target_team"))
	{
		result->m_target_team = parameter["target_team"];
	}
    if (parameter.contains("agent"))
    {
        result->m_agent = parameter["agent"];
    }
    return result;
}
