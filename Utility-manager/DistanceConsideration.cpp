#include "DistanceConsideration.h"

#include <limits>
#include "MathFunctions.h"

DistanceConsideration::DistanceConsideration()
{
}

float DistanceConsideration::compute(BlackboardManager& bm)
{
    auto from = m_from.getPtr<Vec2D>(bm);
    auto to = m_to.getPtr<Vec2D>(bm);
    if (!(from && to))
        return std::numeric_limits<float>::max();

    Vec2D direction{ to->x - from->x, to->y - from->y };

    return sqrt(direction.x * direction.x + direction.y * direction.y);
}
std::unique_ptr<IConsideration> DistanceConsideration::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
    auto result = std::make_unique<DistanceConsideration>();
    if (parameter.contains("from"))
    {
        result->m_from.init( agent, team, parameter["from"]);
    }
    if (parameter.contains("to"))
    {
        result->m_to.init( agent, team, parameter["to"]);
    }
    return result;
}
