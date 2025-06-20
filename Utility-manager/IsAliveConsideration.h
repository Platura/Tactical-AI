#pragma once
#include "IConsideration.h"
#include "BlackboardAddr.h"
class IsAliveConsideration :
    public IConsideration
{
    aiTeamId m_target_team = 0;
    BlackboardAddr m_target;


public:
    //Checks if the set Target is alive
    IsAliveConsideration();
    float compute(BlackboardManager& bm) override;
    static std::unique_ptr<IConsideration> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);
    void DrawDebugUi() {};
};

