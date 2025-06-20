#include "AmbushSensor.h"
#include "AgentVisibilityMap.h"
#include "EngineDebugData.h"
#include "TacticalMap.h"
#include <fmt/format.h>

std::unique_ptr<ISensor> AmbushSensor::create(json const& parameter)
{
	auto ptr = std::make_unique<AmbushSensor>();

	if (parameter.contains("field_name"))
	{
		ptr->m_field_name = parameter["field_name"];
	}
	if (parameter.contains("team_id"))
	{
		ptr->m_team = parameter["team_id"];
	}
	return std::move(ptr);
}

void AmbushSensor::update(BlackboardManager& bm, IEngineDataInput* data)
{
	auto ids = bm.getAgents(m_team);
	auto bb_ptr = bm.getAgentBlackboard(m_agent).getValuePtr<TacticalMap>(m_field_name);
	if (isFirstTime)
	{
		EngineDebugData::getInstance()->register_map(bb_ptr, fmt::format("Ambush Map agent {}", m_agent));
		isFirstTime = false;
	}

	auto map_size = data->getMapSize();

	
	std::vector<TacticalMap> vis_maps;
	for (int i = 0; i < ids.size(); ++i)
	{
		auto ptr = bm.getAgentBlackboard(ids[i]).getValuePtrOr<TacticalMap>("agent_vis");
		if (ptr && ptr->getSize() != 0)
			vis_maps.push_back(*ptr);
	}
	AgentVisibilityMap target_360;
	InputEntity entity;
	entity.pos = data->getAgentPosition(m_agent);
	entity.pos.x /= 32;
	entity.pos.y /= 32;

	entity.direction = InputEntity::no;
	entity.visibility_range = 5;
	auto costmap = data->getCostField();
	TacticalMap target_vis = target_360.compute360(costmap, entity);

	*bb_ptr = m_ambush.compute(vis_maps,target_vis);
}
