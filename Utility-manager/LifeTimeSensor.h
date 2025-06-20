#pragma once
#include "ISensor.h"
#include <memory>

/*
Usage:

{
	"Type":"LifeTimeSensor",
	"field_name":"life_time"
}

*/

class LifeTime :
    public ISensor
{
	uint64_t m_ticks = 0;
	std::string m_field_name = "LifeTime";

public:

	void update(BlackboardManager& bm, IEngineDataInput* data) override;

	static std::unique_ptr<ISensor> create(json const& parameter);

};

