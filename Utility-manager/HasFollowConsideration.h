#pragma once
#include"IConsideration.h"
#include "BlackboardAddr.h"
class HasFollowConsideration :
    public IConsideration
{
public:
    HasFollowConsideration();
    float compute(BlackboardManager& bm);
    static std::unique_ptr<IConsideration> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);

};

