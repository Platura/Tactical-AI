#pragma once
#include "IConsideration.h"
#include "BlackboardAddr.h"

class DistanceConsideration :
    public IConsideration
{
    BlackboardAddr m_from;
    BlackboardAddr m_to;


public:
    DistanceConsideration();
    float compute(BlackboardManager& bm) override;
    static std::unique_ptr<IConsideration> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);
    void DrawDebugUi() {};
};

