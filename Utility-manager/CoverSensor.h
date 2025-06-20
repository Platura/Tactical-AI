#pragma once
#include "ISensor.h"
#include "BlackboardAddr.h"
#include <memory>
#include "CoverMap.h"
class CoverSensor : public ISensor
{
private:
    std::string m_field_name = "Cover";
    bool isFirstTime = true;
    CoverMap cover;
public:
    static std::unique_ptr<ISensor> create(json const& parameter);
    void update(BlackboardManager& bm, IEngineDataInput* data);
};

