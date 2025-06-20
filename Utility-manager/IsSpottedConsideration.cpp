#include "IsSpottedConsideration.h"

IsSpottedConsideration::IsSpottedConsideration()
{
}

float IsSpottedConsideration::compute(BlackboardManager& bm)
{
	auto spotted_value = bm.getAgentBlackboard(m_agent).getValue<aiFloat>("is_spotted");
	if (spotted_value.has_value())
	{

		return spotted_value.value();
	}
		

	return 0;
}

std::unique_ptr<IConsideration> IsSpottedConsideration::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<IsSpottedConsideration>();

	return result;
}
