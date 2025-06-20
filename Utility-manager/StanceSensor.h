#pragma once
#include "ISensor.h"
#include <memory>
class StanceSensor :
    public ISensor
{
private:
    std::string m_field_name = "Stance";
public:
    void update(BlackboardManager& bm, IEngineDataInput* data) override;
    static std::unique_ptr<ISensor> create(json const& parameter);
};

