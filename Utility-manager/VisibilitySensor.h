#pragma once
#include "ISensor.h"
#include "BlackboardAddr.h"
#include <memory>
#include "AgentVisibilityMap.h"
class VisibilitySensor: public ISensor
{
private:
    int m_from_team = 0;
    std::string m_field_name = "Visibility";
    bool isFirstTime = true;
    AgentVisibilityMap visibility;
public:
    static std::unique_ptr<ISensor> create(json const& parameter);
    void update(BlackboardManager& bm, IEngineDataInput* data);
    
};

