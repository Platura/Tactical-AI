#include "SpottedSensor.h"

#include "EngineDebugData.h"
#include <fmt/format.h>

std::unique_ptr<ISensor> SpottedSensor::create(json const& parameter)
{
	auto ptr = std::make_unique<SpottedSensor>();

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

void SpottedSensor::update(BlackboardManager& bm, IEngineDataInput* data)
{
	auto ids = bm.getAgents(m_from_team);
	auto bb_ptr = bm.getAgentBlackboard(m_agent).getValuePtr<TacticalMap>(m_field_name);
	
	auto agent_ids = bm.getAgents(bm.getTeam(m_agent));
	if (isFirstTime)
	{
		EngineDebugData::getInstance()->register_map(bb_ptr, fmt::format("Spotted Map agent {}", m_agent));
		isFirstTime = false;
	}
	auto map_size = data->getMapSize();
	TacticalMap combined_vis(map_size.tiles_x, map_size.tiles_y);

	for (int enemy_id : ids)
	{
		//combine every visibility_map into the combined_vis
		auto vis_map = bm.getAgentBlackboard(enemy_id).getValue<TacticalMap>("agent_vis");
		if (!vis_map.has_value())
		{
			InputEntity entity;
			entity.pos = data->getAgentPosition(enemy_id);
			entity.pos.x /= 32;
			entity.pos.y /= 32;

			entity.direction = directionFromRotation(data->getAgentRotation(enemy_id));
			entity.visibility_range = 5;
			vis_map = visibility.compute(data->getCostField(), entity);
			bm.getAgentBlackboard(enemy_id).setValue("agent_vis", vis_map.value());
		}
		combined_vis.max(vis_map.value());

		// Track agents seen by this enemy
		std::vector<aiAgentId> spotted_agents;

		//check for every agent if he has been spotted by an enemy
		for (int agent_id : agent_ids)
		{
			float randomValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			auto current_agent_pos = bm.getAgentBlackboard(agent_id).getValue<aiPosition>("position");
			if (!current_agent_pos.has_value())
				continue;
			auto visible_value = vis_map.value().at(current_agent_pos.value().x/32, current_agent_pos.value().y/32);
			if (visible_value == 0  || visible_value<randomValue)
			{
				bm.getAgentBlackboard(agent_id).setValue("is_spotted", 0);
			}
			else
			{
				bm.getAgentBlackboard(agent_id).setValue("is_spotted", 1);
				spotted_agents.push_back(agent_id);
			}
		}

		bm.getAgentBlackboard(enemy_id).setValue("spotted_agents", spotted_agents);

	}

	*bb_ptr = combined_vis;
	bm.getGlobal().setValue("combined_vis", *bb_ptr);
}