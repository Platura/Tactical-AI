#pragma once
#include "IConsideration.h"
#include "BlackboardAddr.h"
class InRangeConsideration :
    public IConsideration
{
    //Consideration for if an Agent is in Range
    BlackboardAddr m_position;
    aiTeamId m_target_team = 0;
    BlackboardAddr m_nearest_id;
    float max_distance = 10.f;

public:
    InRangeConsideration();
    float compute(BlackboardManager& bm) override;
    static std::unique_ptr<IConsideration> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);
    void DrawDebugUi() {};
};

