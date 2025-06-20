#include "IsAliveConsideration.h"

IsAliveConsideration::IsAliveConsideration()
{
}

float IsAliveConsideration::compute(BlackboardManager& bm)
{
    auto agent_target=bm.getAgentBlackboard(m_agent).getValue<aiAgentId>("agent_target");
    if (!agent_target || agent_target.value() == 0)
        return 0;

    auto target_pos = bm.getAgentBlackboard(agent_target.value()).getValue<aiPosition>("position");
    if (target_pos.has_value())
        return 1;
    else {
        return 0;
    }
}

std::unique_ptr<IConsideration> IsAliveConsideration::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
    auto result = std::make_unique<IsAliveConsideration>();
    if (parameter.contains("agent"))
    {
        result->m_agent = parameter["agent"];
    }
    if (parameter.contains("target"))
    {
        result->m_target.init(agent, team, parameter["target"]);
    }
    return result;
}
