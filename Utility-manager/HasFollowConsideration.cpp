#include "HasFollowConsideration.h"
HasFollowConsideration::HasFollowConsideration()
{
}

float HasFollowConsideration::compute(BlackboardManager& bm)
{
    if (bm.getAgentBlackboard(m_agent).getValue<aiAgentId>("front_agent").has_value())
    {
        return 1.f;
    }
    return 0.f;
}

std::unique_ptr<IConsideration> HasFollowConsideration::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
    auto result = std::make_unique<HasFollowConsideration>();
    return result;
}
