#include "LifeTimeSensor.h"

void LifeTime::update(BlackboardManager& bm, IEngineDataInput* data)
{
	m_ticks += 1;

	bm.getAgentBlackboard(m_agent).setValue(m_field_name, m_ticks);
}

std::unique_ptr<ISensor>  LifeTime::create(json const& parameter)
{
	auto ptr = std::make_unique<LifeTime>();

	if (parameter.contains("field_name"))
	{
		ptr->m_field_name = parameter["field_name"];
	}
	return std::move(ptr);
}
