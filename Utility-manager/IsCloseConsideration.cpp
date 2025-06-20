#include "IsCloseConsideration.h"

IsCloseConsideration::IsCloseConsideration()
{
}
float IsCloseConsideration::compute(BlackboardManager& bm)
{
    auto agent_pos = bm.getAgentBlackboard(m_agent).getValue<aiPosition>("position");
    auto front_id = bm.getAgentBlackboard(m_agent).getValue<aiAgentId>("front_agent");
    if (!front_id.has_value())
    {
        return 0;
    }
    auto front_pos = bm.getAgentBlackboard(front_id.value()).getValue<aiPosition>("position");
    if (!agent_pos.has_value() || !front_pos.has_value()) {
        return 0.0f;
    }
    int dx = abs(agent_pos.value().x - front_pos.value().x);
    int dy = abs(agent_pos.value().y - front_pos.value().y);
    int distance = dx + dy;
    if (distance < 2)
    {
        return 1;
    }
    return 1 - (std::clamp(((distance - 2) / max_distance), 0, 1));
}

std::unique_ptr<IConsideration> IsCloseConsideration::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
    auto result = std::make_unique<IsCloseConsideration>();
    return result;
}