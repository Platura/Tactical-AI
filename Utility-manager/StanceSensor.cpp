#include "StanceSensor.h"

void StanceSensor::update(BlackboardManager& bm, IEngineDataInput* data)
{
	bm.getAgentBlackboard(m_agent).setValue(m_field_name, data->getAgentStance(m_agent));
}

std::unique_ptr<ISensor> StanceSensor::create(json const& parameter)
{
	auto ptr = std::make_unique<StanceSensor>();

	if (parameter.contains("field_name"))
	{
		ptr->m_field_name = parameter["field_name"];
	}
	return std::move(ptr);
}
