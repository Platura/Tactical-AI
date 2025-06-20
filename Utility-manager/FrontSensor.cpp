#include "FrontSensor.h"
#include "MovementMap.h"
#include "InfluenceMap.h"
#include "EngineDebugData.h"
#include <fmt/format.h>

std::unique_ptr<ISensor> FrontSensor::create(json const& parameter)
{
    auto ptr = std::make_unique<FrontSensor>();
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

void FrontSensor::update(BlackboardManager& bm, IEngineDataInput* data)
{
	currentFrame++;
	if (currentFrame<updateInterval)
		return;

	auto threat = bm.getTeamBlackboard(1).getValue<InfluenceMap>("Threat");
	if (!threat.has_value())
		return;

	TacticalMap threat_map = threat.value().getFieldSum();

	auto movement_map = bm.getAgentBlackboard(m_team).getValue<TacticalMap>("movement_map");
	if (!movement_map.has_value())
	{
		MovementMap movement;
		auto agent_pos = bm.getAgentBlackboard(m_agent).getValue<aiPosition>("position");
		movement_map = movement.compute(agent_pos.value(), data->getCostField());
	}
	const float a = 1.f;
	movement_map.value() /= 10;
	movement_map.value() += a;
	TacticalMap front_map = threat_map / movement_map.value();
	TacticalMap save_map = threat.value().getFieldSave();
	*bm.getTeamBlackboard(m_team).getValuePtr<TacticalMap>("front_map") = front_map;
	*bm.getGlobal().getValuePtr<TacticalMap>("save_map") = save_map;
	currentFrame = 0;
}