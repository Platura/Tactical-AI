#include "RemoveTargetAction.h"

void RemoveTargetAction::action(BlackboardManager& bm)
{
	bm.getAgentBlackboard(m_agent).removeValue("agent_target");
}

std::unique_ptr<IAction> RemoveTargetAction::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<RemoveTargetAction>();

	if (parameter.contains("agent"))
	{
		result->m_agent = parameter["agent"];
	}


	return result;
}
