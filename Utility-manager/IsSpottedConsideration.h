#pragma once
#include "IConsideration.h"
#include "BlackboardAddr.h"
class IsSpottedConsideration :
    public IConsideration
{
    BlackboardAddr m_value;

public:
    //Checks if the Agent has been spotted
    IsSpottedConsideration();
    float compute(BlackboardManager& bm) override;
    static std::unique_ptr<IConsideration> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);
};



