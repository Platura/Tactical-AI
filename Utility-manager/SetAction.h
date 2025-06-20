#pragma once
#include "IOneTimeAction.h"
#include "BlackboardAddr.h"

class SetAction :
    public IOneTimeAction
{
    BlackboardAddr m_field;
    values m_value = { aiNone{} };
public:

    void action(BlackboardManager& bm) override;

    static std::unique_ptr<IAction> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);

};

