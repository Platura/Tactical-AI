#pragma once
#include "ISensor.h"
#include "BlackboardAddr.h"
#include <memory>
#include "MovementMap.h"
class TestMovementSensor : public ISensor
{
private:
    std::string m_field_name = "TestMovement";
    bool isFirstTime = true;
    MovementMap move_map;
public:
    static std::unique_ptr<ISensor> create(json const& parameter);
    void update(BlackboardManager& bm, IEngineDataInput* data);
};

