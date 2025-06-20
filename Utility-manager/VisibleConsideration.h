#pragma once
#include "IConsideration.h"
#include "BlackboardAddr.h"
class VisibleConsideration :
    public IConsideration
{
    //max_vis currently 10
    aiTeamId m_target_team = 0;

public:
    VisibleConsideration();
    float compute(BlackboardManager& bm) override;
    static std::unique_ptr<IConsideration> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);
    void DrawDebugUi() {};
};

