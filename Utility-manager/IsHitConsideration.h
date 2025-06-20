#pragma once
#include "IConsideration.h"
#include "BlackboardAddr.h"
class IsHitConsideration :
    public IConsideration
{
private:
    int max_health = 100;
    float last_value = 0;
public:
    IsHitConsideration();
    float compute(BlackboardManager& bm) override;
    static std::unique_ptr<IConsideration> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);
};

