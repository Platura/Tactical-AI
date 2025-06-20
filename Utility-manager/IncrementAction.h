#pragma once
#include "IOneTimeAction.h"
#include "BlackboardAddr.h"

class IncrementAction :
    public IOneTimeAction
{
    BlackboardAddr m_name;
public:
    void action(BlackboardManager& bm) override;

    static std::unique_ptr<IAction> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);

};

