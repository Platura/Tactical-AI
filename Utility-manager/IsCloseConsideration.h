#pragma once
#include "IConsideration.h"
#include "BlackboardAddr.h"
class IsCloseConsideration :
    public IConsideration
{

    int max_distance = 50 - 2;
public:
    IsCloseConsideration();
    float compute(BlackboardManager& bm) override;
    static std::unique_ptr<IConsideration> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);
};

