#pragma once
#include "IConsideration.h"
#include "BlackboardAddr.h"
class AmmunitionConsideration :
    public IConsideration
{
    BlackboardAddr m_max_munition;

public:
    AmmunitionConsideration();
    float compute(BlackboardManager& bm) override;
    static std::unique_ptr<IConsideration> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);
    void DrawDebugUi() {};
};

