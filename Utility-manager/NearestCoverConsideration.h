#pragma once
#include "IConsideration.h"
#include "BlackboardAddr.h"
class NearestCoverConsideration :
    public IConsideration
{
    BlackboardAddr m_nearest_cover;

public:
    NearestCoverConsideration();
    //check if the current front is still the front
    float compute(BlackboardManager& bm) override;
    static std::unique_ptr<IConsideration> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);
    void DrawDebugUi() {};
};

