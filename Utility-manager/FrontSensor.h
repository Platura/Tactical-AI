#pragma once
#include "ISensor.h"
#include "BlackboardAddr.h"
#include <memory>
class FrontSensor :
    public ISensor
{
private:
    int m_from_team = 0;
    std::string m_field_name = "Front";
    bool isFirstTime = true;
    int updateInterval = 1000;
    int currentFrame = 1001;
public:
    //calculates the summed threatmap/movementmap
    static std::unique_ptr<ISensor> create(json const& parameter);
    void update(BlackboardManager& bm, IEngineDataInput* data);
};

