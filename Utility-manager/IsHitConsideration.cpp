#include "IsHitConsideration.h"
#include <cmath>
IsHitConsideration::IsHitConsideration()
{
}

float IsHitConsideration::compute(BlackboardManager& bm)
{
	auto last_health = bm.getAgentBlackboard(m_agent).getValue<aiInt>("last_hp");
	
	auto current_health = bm.getAgentBlackboard(m_agent).getValue<aiInt>("current_hp");
	if (!last_health.has_value())
	{
		bm.getAgentBlackboard(m_agent).setValue("last_hp", current_health.value());
		return 0;
	}
		

	if (current_health.value() < last_health.value())
	{
		bm.getAgentBlackboard(m_agent).setValue("last_hp", current_health.value());
		last_value = 1.f;
	}

	last_value = std::max(0.f, last_value - 0.001f);

	return last_value;
}

std::unique_ptr<IConsideration> IsHitConsideration::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<IsHitConsideration>();
	return result;
}
