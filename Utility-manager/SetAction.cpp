#include "SetAction.h"

void SetAction::action(BlackboardManager& bm)
{
	m_field.getVariant(bm) = m_value;
}

std::unique_ptr<IAction> SetAction::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<SetAction>();

	if (parameter.contains("name"))
	{
		result->m_field.init(agent, team, parameter["name"]);
	}
	if (parameter.contains("value"))
	{
		result->m_value = valuesFromJson(parameter["value"]);
	}

	return result;
}
