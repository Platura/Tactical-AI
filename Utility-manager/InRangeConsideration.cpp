#include "InRangeConsideration.h"
#include <fmt/format.h>
#include <algorithm>

InRangeConsideration::InRangeConsideration()
{
}

float InRangeConsideration::compute(BlackboardManager& bm)
{
	aiPosition agent_pos = *m_position.getPtr<aiPosition>(bm);
	aiAgentId nearest_id = *m_nearest_id.getPtr<aiAgentId>(bm);
	if (nearest_id == 0)
	{
		return std::numeric_limits<float>::max();
	}

	auto target_pos = bm.getAgentBlackboard(nearest_id).getValue<aiPosition>("position").value();
	
	Vec2D direction{ target_pos.x - agent_pos.x, target_pos.y - agent_pos.y };
	auto distance = sqrt(direction.x * direction.x + direction.y * direction.y);
	//0 less distance 1 too far
	return std::min(distance / max_distance, 1.f);
}

std::unique_ptr<IConsideration> InRangeConsideration::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<InRangeConsideration>();


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
