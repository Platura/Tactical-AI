#include "MoveToAction.h"

void MoveToAction::onActionStart(BlackboardManager& bm, IEngineDataOutput* cmd, IEngineDataInput*)
{
	auto bb_has_mod_cost = bm.getAgentBlackboard(m_agent).getValue<Costfield>("modified_cost");
	
	auto bb_has_pos_target = bm.getAgentBlackboard(m_agent).getValue<aiPosition>("position_target");
	if (bb_has_pos_target.has_value())
	{
		*m_target.getPtr<aiPosition>(bm) = bb_has_pos_target.value();
	}
	if (bb_has_mod_cost.has_value())
	{
		cmd->moveTo(m_agent, *m_target.getPtr<aiPosition>(bm), bb_has_mod_cost.value());
	}
	else {
		cmd->moveTo(m_agent, *m_target.getPtr<aiPosition>(bm));
	}
	
}

void MoveToAction::onActionUpdate(BlackboardManager& bm, IEngineDataOutput* cmd)
{
	m_isFinished = !cmd->isActionRunning(m_agent);
}

void MoveToAction::onActionFinished(BlackboardManager& bm, IEngineDataOutput* cmd)
{
	if (cmd->isActionRunning(m_agent))
	{
		cmd->stopAction(m_agent);

	}
}

std::unique_ptr<IAction> MoveToAction::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<MoveToAction>();

	if (parameter.contains("target"))
	{
		result->m_target.init(agent, team, parameter["target"]);
	}

	return result;
}
