#pragma once
#include "IOneTimeAction.h"
#include "BlackboardAddr.h"
class RemoveTargetAction :
    public IOneTimeAction
{
private:
public:
    void action(BlackboardManager& bm) override;
    static std::unique_ptr<IAction> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);

};

