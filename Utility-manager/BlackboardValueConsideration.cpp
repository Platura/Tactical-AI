#include "BlackboardValueConsideration.h"
#include <fmt/format.h>
BlackboardValueConsideration::BlackboardValueConsideration()
{
}

float BlackboardValueConsideration::compute(BlackboardManager& bm)
{
	return *m_value.getPtr<float>(bm);
}

std::unique_ptr<IConsideration> BlackboardValueConsideration::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	
	auto result = std::make_unique<BlackboardValueConsideration>();
	

	if (!parameter.contains("value"))
	{
		fmt::print("[ERROR] BlackboardValueConsideration: missing field value");
		return nullptr;
	}
	else
	{
		result->m_value.init(agent, team, parameter["value"]);
	}

	return result;
}
