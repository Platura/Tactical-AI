#include "VisibilitySensor.h"

#include "EngineDebugData.h"
#include <fmt/format.h>

std::unique_ptr<ISensor> VisibilitySensor::create(json const& parameter)
{
	auto ptr = std::make_unique<VisibilitySensor>();

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

void VisibilitySensor::update(BlackboardManager& bm, IEngineDataInput* data)
{
	//auto ids = bm.getAgents(m_from_team);
	auto bb_ptr = bm.getAgentBlackboard(m_agent).getValuePtr<TacticalMap>(m_field_name);
	if (isFirstTime)
	{
		EngineDebugData::getInstance()->register_map(bb_ptr, fmt::format("Visibility Map agent {}", m_agent));
		isFirstTime = false;
	}

	auto map_size = data->getMapSize();

	//std::vector<InputEntity> entities(ids.size(),InputEntity{});
	/*for (int i = 0; i < ids.size(); ++i)
	{
		entities[i].pos = data->getAgentPosition(ids[i]);
		entities[i].type = 0;
	}*/
	InputEntity entity;
	entity.pos = data->getAgentPosition(m_agent);
	entity.pos.x /= 32;
	entity.pos.y /= 32;

	entity.direction = directionFromRotation(data->getAgentRotation(m_agent));
	entity.visibility_range = 5;

	*bb_ptr = visibility.compute(data->getCostField(), entity);
	bm.getAgentBlackboard(m_agent).setValue("agent_vis", *bb_ptr);
}
