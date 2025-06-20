#pragma once
#include "ISensor.h"
class CostSensor :
    public ISensor
{
	std::string m_field_name = "Cost";
	bool isFirstTime = true;
public:
	void update(BlackboardManager& bm, IEngineDataInput* data) override;

	static std::unique_ptr<ISensor> create(json const& parameter);
};

