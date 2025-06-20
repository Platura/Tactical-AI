#include "PositionSensor.h"

void PositionSensor::update(BlackboardManager& bm, IEngineDataInput* data)
{
	bm.getAgentBlackboard(m_agent).setValue(m_field_name, data->getAgentPosition(m_agent));
}

std::unique_ptr<ISensor> PositionSensor::create(json const& parameter)
{
	auto ptr = std::make_unique<PositionSensor>();

	if (parameter.contains("field_name"))
	{
		ptr->m_field_name = parameter["field_name"];
	}
	return std::move(ptr);
}
