#include "HealthConsideration.h"

HealthConsideration::HealthConsideration()
{
}

float HealthConsideration::compute(BlackboardManager& bm)
{
    auto currentHp = bm.getAgentBlackboard(m_agent).getValue<aiInt>("current_hp");
    auto maxHp = bm.getGlobal().getValue<aiInt>("max_health");
    float result = (float) currentHp.value() / (float) maxHp.value();
    return result;
}

std::unique_ptr<IConsideration> HealthConsideration::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
    auto result = std::make_unique<HealthConsideration>();
    if (parameter.contains("max_health"))
    {
        result->m_max_hp.init(agent, team, parameter["max_health"]);
    }
    return result;
}
