#include "ThreatSensor.h"
#include "InfluenceMap.h"
#include "EngineDebugData.h"
#include <fmt/format.h>

std::unique_ptr<ISensor> ThreatSensor::create(json const& parameter)
{
	auto ptr = std::make_unique<ThreatSensor>();

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
void ThreatSensor::update(BlackboardManager& bm, IEngineDataInput* data)
{
	auto ids = bm.getAgents(m_from_team);

	auto bb_ptr = bm.getTeamBlackboard(m_team).getValuePtr<InfluenceMap>(m_field_name);
	if(isFirstTime)
	{
		 EngineDebugData::getInstance()->register_map(&bb_ptr->getField(), fmt::format("Threat Map Agent {}", m_agent));
		 isFirstTime = false;
	}

	auto& threat = *bb_ptr;

	auto map_size = data->getMapSize();
	threat.init(map_size.tiles_x, map_size.tiles_y, map_size.tile_size_X, map_size.tile_size_y);
	//current basic template
	threat.createLinearTemplate(0, 5);

	std::vector<AgentEntity> entities(ids.size(), AgentEntity{});

	for (int i = 0; i < ids.size(); ++i)
	{
		entities[i].pos = data->getAgentPosition(ids[i]);
		entities[i].type = 0;
	}
	
	threat.compute(entities, data->getCostField());

}
