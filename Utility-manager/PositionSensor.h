#pragma once
#include "ISensor.h"
#include <memory>
/*
Usgae:

{
	"Type":"PositionSensor",
	"field_name":"positon"
}

*/
class PositionSensor :
	public ISensor
{
	std::string m_field_name = "Position";
public:
	void update(BlackboardManager& bm, IEngineDataInput* data) override;

	static std::unique_ptr<ISensor> create(json const& parameter);
};

