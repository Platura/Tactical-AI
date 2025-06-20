#pragma once
#include "ISensor.h"
class GlobalVisibilitySensor :
    public ISensor
{
private:
    std::string m_field_name = "GlobalVis";
    bool isFirstTime = true;
public:
    static std::unique_ptr<ISensor> create(json const& parameter);
    void update(BlackboardManager& bm, IEngineDataInput* data);
};

