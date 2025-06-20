#include "HasTargetConsideration.h"

HasTargetConsideration::HasTargetConsideration()
{
}

float HasTargetConsideration::compute(BlackboardManager& bm)
{
    if (bm.getAgentBlackboard(m_agent).getValue<aiAgentId>("agent_target").has_value())
    {
        return 1.f;
    }
    return 0.f;
}

std::unique_ptr<IConsideration> HasTargetConsideration::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
    auto result = std::make_unique<HasTargetConsideration>();
    return result;
}
