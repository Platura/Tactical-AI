#pragma once
#include "IConsideration.h"
#include "BlackboardAddr.h"
class HasTargetConsideration :
    public IConsideration
{
    aiTeamId m_target_team = 0;
public:
    //Checks if a Target is set
    HasTargetConsideration();
    float compute(BlackboardManager& bm) override;
    static std::unique_ptr<IConsideration> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);
    void DrawDebugUi() {};
};

