#include "CostSensor.h"
#include "EngineDebugData.h"
#include <fmt/format.h>

void CostSensor::update(BlackboardManager& bm, IEngineDataInput* data)
{
	auto bb_ptr = bm.getGlobal().getValuePtr<Costfield>(m_field_name);
	if (isFirstTime)
	{
		//EngineDebugData::getInstance()->register_map(bb_ptr, fmt::format("costmap"));
		*bb_ptr = data->getCostField();
		isFirstTime = false;
	}
}

std::unique_ptr<ISensor> CostSensor::create(json const& parameter)
{
	auto ptr = std::make_unique<CostSensor>();

	if (parameter.contains("field_name"))
	{
		ptr->m_field_name = parameter["field_name"];
	}
	return std::move(ptr);
}
