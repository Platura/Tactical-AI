#pragma once
#include "ISensor.h"
#include "BlackboardAddr.h"
#include "AmbushMap.h"
#include <memory>
class AmbushSensor:public ISensor
{
private:
    int m_from_team = 0;
    std::string m_field_name = "Ambush";
    bool isFirstTime = true;
    AmbushMap m_ambush;
public:
    static std::unique_ptr<ISensor> create(json const& parameter);
    void update(BlackboardManager& bm, IEngineDataInput* data);

};

