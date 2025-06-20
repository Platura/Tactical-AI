#pragma once
#include "ISensor.h"
#include "BlackboardAddr.h"
#include <memory>

class ThreatSensor :
    public ISensor
{
private:
    int m_from_team = 0;
    std::string m_field_name = "Threat";
    bool isFirstTime = true;
public:
    static std::unique_ptr<ISensor> create(json const& parameter);
    void update(BlackboardManager& bm, IEngineDataInput* data);
};

