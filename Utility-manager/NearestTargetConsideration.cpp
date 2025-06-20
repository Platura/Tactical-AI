#include "NearestTargetConsideration.h"
#include <fmt/format.h>

NearestTargetConsideration::NearestTargetConsideration()
{
}

float NearestTargetConsideration::compute(BlackboardManager& bm)
{
	float min_distance = std::numeric_limits<float>::max();
	aiAgentId nearest_target = 0;
	aiPosition agent_pos = *m_position.getPtr<aiPosition>(bm);
	auto target_ids = bm.getAgents(m_target_team);
	for (int i = 0; i < target_ids.size(); ++i)
	{
		auto target_pos = bm.getAgentBlackboard(target_ids.at(i)).getValue<aiPosition>("position");
		if (!target_pos.has_value())
			continue;
		if (!(agent_pos.x && target_pos.value().x && agent_pos.y && target_pos.value().y))
			continue;

		Vec2D direction{ target_pos.value().x - agent_pos.x, target_pos.value().y - agent_pos.y };
		auto distance = sqrt(direction.x * direction.x + direction.y * direction.y);

		if (distance < min_distance)
		{
			min_distance = distance;
			nearest_target = target_ids.at(i);
		}
			
	}
	*m_nearest_id.getPtr<aiAgentId>(bm) = nearest_target;
	return min_distance;
}

std::unique_ptr<IConsideration> NearestTargetConsideration::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<NearestTargetConsideration>();

	 
	if (parameter.contains("target_team"))
	{
		result->m_target_team = parameter["target_team"];
	}
	
	if (!parameter.contains("nearest_id"))
	{
		fmt::print("[ERROR] NearestTargetConsideration missing field nearest_id");
		return nullptr;
	}
	else
	{
		result->m_nearest_id.init(agent, team, parameter["nearest_id"]);
	}

	if (!parameter.contains("position"))
	{
		fmt::print("[ERROR] NearestTargetConsideration missing field position");
		return nullptr;
	}
	else
	{
		result->m_position.init(agent, team, parameter["position"]);
	}

	return result;
}
