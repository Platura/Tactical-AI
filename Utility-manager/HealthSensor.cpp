#include "HealthSensor.h"

std::unique_ptr<ISensor> HealthSensor::create(json const& parameter)
{
	auto ptr = std::make_unique<HealthSensor>();

	if (parameter.contains("field_name"))
	{
		ptr->m_field_name = parameter["field_name"];
	}
	return std::move(ptr);
}

void HealthSensor::update(BlackboardManager& bm, IEngineDataInput* data)
{
	auto bb_ptr = bm.getAgentBlackboard(m_agent).getValuePtr<aiInt>(m_field_name);
	auto current_hp = data->getAgentHealth(m_agent);
	*bb_ptr = current_hp;
}
