#include "ComputeCostAction.h"
#include "AgentVisibilityMap.h"

void ComputeCostAction::onActionStart(BlackboardManager& bm, IEngineDataOutput*cmd, IEngineDataInput*data)
{
	m_cost = data->getCostField();
	TacticalMap costf = m_cost.convert<float>([](uint32_t v) {return float(v); });
	AgentVisibilityMap vis_map;
	InputEntity entity;
	auto agent_target = bm.getAgentBlackboard(m_agent).getValue<aiAgentId>("agent_target").value();
	entity.pos = bm.getAgentBlackboard(agent_target).getValue<aiPosition>("position").value();
	entity.pos.x /= 32;
	entity.pos.y /= 32;
	entity.direction = directionFromRotation(data->getAgentRotation(m_agent));
	entity.visibility_range = 5.f;
	TacticalMap vis = vis_map.compute(m_cost, entity);
	costf.max(vis.weight(19));
	m_cost.init(costf);
}

void ComputeCostAction::onActionUpdate(BlackboardManager& bm, IEngineDataOutput*)
{
	m_isFinished = true;
}

void ComputeCostAction::onActionFinished(BlackboardManager& bm, IEngineDataOutput*)
{
	*m_mod_cost.getPtr<Costfield>(bm) = m_cost;
}

std::unique_ptr<IAction> ComputeCostAction::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<ComputeCostAction>();

	if (parameter.contains("modified_cost"))
	{
		result->m_mod_cost.init(agent, team, parameter["modified_cost"]);
	}

	return result;
}
