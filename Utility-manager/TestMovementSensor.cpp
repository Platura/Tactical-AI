#include "TestMovementSensor.h"
#include "EngineDebugData.h"
#include <fmt/format.h>

std::unique_ptr<ISensor> TestMovementSensor::create(json const& parameter)
{
	auto ptr = std::make_unique<TestMovementSensor>();
	if (parameter.contains("field_name"))
	{
		ptr->m_field_name = parameter["field_name"];
	}
	return std::move(ptr);
}

void TestMovementSensor::update(BlackboardManager& bm, IEngineDataInput* data)
{
	auto bb_ptr = bm.getGlobal().getValuePtr<TacticalMap>(m_field_name);
	if (isFirstTime)
	{
		EngineDebugData::getInstance()->register_map(bb_ptr, fmt::format("movement_test"));
		*bb_ptr = move_map.compute({ 44*32,48*32 }, data->getCostField());
		isFirstTime = false;
	}

}
