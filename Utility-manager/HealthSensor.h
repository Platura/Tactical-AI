#pragma once
#include "ISensor.h"
class HealthSensor :
    public ISensor
{
private:
    std::string m_field_name = "current_hp";
public:
    static std::unique_ptr<ISensor> create(json const& parameter);
    void update(BlackboardManager& bm, IEngineDataInput* data);

};

