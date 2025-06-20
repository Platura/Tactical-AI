#include "SelectTargetAction.h"

void SelectTargetAction::onActionStart(BlackboardManager& bm, IEngineDataOutput*cmd, IEngineDataInput*)
{
	auto bb_has_nearest_id = bm.getAgentBlackboard(m_agent).getValue<aiAgentId>("nearest_id");
	if(bb_has_nearest_id.has_value())
		agent_target_id = bb_has_nearest_id.value();
	else
		agent_target_id = 2;
}

void SelectTargetAction::onActionUpdate(BlackboardManager& bm, IEngineDataOutput*cmd)
{
	m_isFinished = true;
}

void SelectTargetAction::onActionFinished(BlackboardManager& bm, IEngineDataOutput*)
{
	*m_agent_target.getPtr<aiAgentId>(bm) = agent_target_id; 
}

std::unique_ptr<IAction> SelectTargetAction::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<SelectTargetAction>();

	if (parameter.contains("agent_target"))
	{
		result->m_agent_target.init(agent, team, parameter["agent_target"]);
	}

	return result;
}
