#pragma once
#include "IConsideration.h"
#include "BlackboardAddr.h"
class NearestTargetConsideration :
    public IConsideration
{
    BlackboardAddr m_position;
    aiTeamId m_target_team = 0;
    BlackboardAddr m_nearest_id;


public:
    //Takes the Position of every Agent of the oposing team and returns the one who is closest
    NearestTargetConsideration();
    float compute(BlackboardManager& bm) override;
    static std::unique_ptr<IConsideration> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);
    void DrawDebugUi() {};
};

