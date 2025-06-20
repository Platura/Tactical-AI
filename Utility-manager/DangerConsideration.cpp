#include "DangerConsideration.h"
#include <fmt/format.h>
#include "InfluenceMap.h"

DangerConsideration::DangerConsideration()
{
}

float DangerConsideration::compute(BlackboardManager& bm)
{
	float sum = 0.f;
	int count = 0;
	auto const pos = *m_position.getPtr<Vec2D>(bm);

	auto threat = m_value.getPtr<InfluenceMap>(bm);

	for (int dx = -radius; dx <= radius; ++dx)
	{
		for (int dy = -radius; dy <= radius; ++dy)
		{
			int x = pos.x + dx;
			int y = pos.y + dy;

			if (x >= 0 && y >= 0 && x < threat->getField().getSizeX() *32 && y < threat->getField().getSizeY() * 32)
			{
				sum += threat->at(x,y);
				count++;
			}
		}
	}

	return count > 0 ? sum / count : 0.f;
}

std::unique_ptr<IConsideration> DangerConsideration::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<DangerConsideration>();



	if (!parameter.contains("value"))
	{
		fmt::print("[ERROR] ThreatConsideration: missing field value");
		return nullptr;
	}
	else
	{
		result->m_value.init(agent, team, parameter["value"]);
	}

	if (!parameter.contains("position"))
	{
		fmt::print("[ERROR] ThreatConsideration: missing field position");
		return nullptr;
	}
	else
	{
		result->m_position.init(agent, team, parameter["position"]);
	}

	return result;
}