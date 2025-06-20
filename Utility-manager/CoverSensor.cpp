#include "CoverSensor.h"

#include "EngineDebugData.h"
#include <fmt/format.h>

std::unique_ptr<ISensor> CoverSensor::create(json const& parameter)
{
	auto ptr = std::make_unique<CoverSensor>();
	if (parameter.contains("field_name"))
	{
		ptr->m_field_name = parameter["field_name"];
	}
	return std::move(ptr);
}

void CoverSensor::update(BlackboardManager& bm, IEngineDataInput* data)
{
	auto bb_ptr = bm.getGlobal().getValuePtr<TacticalMap>(m_field_name);
	auto bb_ptr2 = bm.getGlobal().getValuePtr<std::vector<std::pair<uint32_t, uint32_t>>>("covers");
	if (isFirstTime)
	{
		EngineDebugData::getInstance()->register_map(bb_ptr, fmt::format("cover"));
		*bb_ptr = cover.compute(data->getCostField());
		*bb_ptr2 = cover.getCover();
		isFirstTime = false;
	}
	Vec2D agent_pos = bm.getAgentBlackboard(m_agent).getValue<aiPosition>("position").value();
	int x = static_cast<int>(agent_pos.x/32);
	int y = static_cast<int>(agent_pos.y/32);

	auto cover_value = bm.getGlobal().getValue<TacticalMap>("cover");
	if (!cover_value.has_value())
		return;
	bm.getAgentBlackboard(m_agent).setValue("cover_value", cover_value.value().at(x,y));
	
}
