#include "ConstConsideration.h"

std::unique_ptr<IConsideration> ConstConsideration::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
    auto result = std::make_unique<ConstConsideration>();
    if (parameter.contains("value"))
    {
        result->value = parameter["value"];
    }
    return result;
}
