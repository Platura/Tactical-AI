#include "ThreatConsideration.h"
#include <fmt/format.h>
#include "InfluenceMap.h"

ThreatConsideration::ThreatConsideration()
{
}

float ThreatConsideration::compute(BlackboardManager& bm)
{
	auto const pos = *m_position.getPtr<Vec2D>(bm);

	auto threat = m_value.getPtr<InfluenceMap>(bm);
	return threat->at(pos.x, pos.y);
}

std::unique_ptr<IConsideration> ThreatConsideration::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<ThreatConsideration>();


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
