#pragma once
#include "IConsideration.h"
#include "BlackboardAddr.h"
class NearestFrontConsideration :
    public IConsideration
{
    int max_distance = 5 - 2;
public:
    NearestFrontConsideration();
    //check if a front is set and if yes is the front_target still the current front
    float compute(BlackboardManager& bm) override;
    static std::unique_ptr<IConsideration> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);
};

 