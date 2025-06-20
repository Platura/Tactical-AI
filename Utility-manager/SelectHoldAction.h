#pragma once
#include "IOneTimeAction.h"
class SelectHoldAction :
    public IOneTimeAction
{
public:
    void action(BlackboardManager& bm) override;
    static std::unique_ptr<IAction> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);
};

