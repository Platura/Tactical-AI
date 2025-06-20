#include "ComputeAmbushAction.h"
#include "AgentVisibilityMap.h"

void ComputeAmbushAction::onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput* data)
{
	auto target_id = bm.getAgentBlackboard(m_agent).getValue<aiAgentId>("agent_target").value();
	auto team_id = bm.getTeam(target_id);
	auto ids = bm.getAgents(team_id);

	std::vector<InputEntity> entities(ids.size(), InputEntity{});
	AgentVisibilityMap visibility_map;
	AgentVisibilityMap target_360;
	std::vector<TacticalMap> vis_maps(ids.size(), TacticalMap{});
	auto cmap = data->getCostField();

	InputEntity entity;
	entity.pos = bm.getAgentBlackboard(target_id).getValue<aiPosition>("position").value();
	entity.pos.x /= 32;
	entity.pos.y /= 32;

	entity.direction = InputEntity::no;
	entity.visibility_range = 5;
	TacticalMap target_vis = target_360.compute360(cmap, entity);

	for (int i = 0; i < ids.size(); ++i)
	{
		entities.at(i).pos = bm.getAgentBlackboard(ids.at(i)).getValue<aiPosition>("position").value();
		entities.at(i).pos.x /= 32;
		entities.at(i).pos.y /= 32;
		entity.direction = directionFromRotation(data->getAgentRotation(m_agent));
		entities.at(i).visibility_range = 5;
		vis_maps.at(i) = visibility_map.compute(cmap, entities.at(i));
	}
	AmbushMap ambush_m;
	compute_ambush = ambush_m.compute(vis_maps, target_vis);
}

void ComputeAmbushAction::onActionUpdate(BlackboardManager& bm, IEngineDataOutput*)
{
	m_isFinished = true;
}

void ComputeAmbushAction::onActionFinished(BlackboardManager& bm, IEngineDataOutput*)
{
	*m_ambush_map.getPtr<TacticalMap>(bm) = compute_ambush;
}

std::unique_ptr<IAction> ComputeAmbushAction::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<ComputeAmbushAction>();

	if (parameter.contains("ambush"))
	{
		result->m_ambush_map.init(agent, team, parameter["ambush"]);
	}

	return result;
}
