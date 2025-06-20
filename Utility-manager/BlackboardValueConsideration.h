#pragma once
#include "IConsideration.h"
#include "BlackboardAddr.h"
class BlackboardValueConsideration :
    public IConsideration
{
    BlackboardAddr m_value;


public:
    BlackboardValueConsideration();
    float compute(BlackboardManager& bm) override;
    static std::unique_ptr<IConsideration> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);
    void DrawDebugUi() {};
};

