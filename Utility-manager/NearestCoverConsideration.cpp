#include "NearestCoverConsideration.h"
#include "MovementMap.h"
#include "HiddenCoverMap.h"
#include "CoverMap.h"

NearestCoverConsideration::NearestCoverConsideration()
{
}

float NearestCoverConsideration::compute(BlackboardManager& bm)
{
    float min_distance = 10;
    auto cmap = bm.getGlobal().getValue<Costfield>("Cost");
    auto agent_pos = bm.getAgentBlackboard(m_agent).getValue<aiPosition>("position");
    MovementMap move_map;
    HiddenCoverMap hidden_cover;
    TacticalMap cover_cost;
    std::vector<std::pair<uint32_t, uint32_t>> covers;

    covers = bm.getGlobal().getValue<std::vector<std::pair<uint32_t, uint32_t>>>("covers").value();
    TacticalMap movement = move_map.compute(agent_pos.value(), cmap.value());
    cover_cost = hidden_cover.computeAverageCost(movement, covers);
    cover_cost /= min_distance;
    for (auto const& el : covers)
    {
        if (cover_cost.at(el.first, el.second) >= 1)
        {
            return 1.f;
        }
    }
    return 0.f;
}

std::unique_ptr<IConsideration> NearestCoverConsideration::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
    auto result = std::make_unique<NearestCoverConsideration>();
    if (parameter.contains("agent"))
    {
        result->m_agent = parameter["agent"];
    }
    if (parameter.contains("nearest_cover"))
    {
        result->m_nearest_cover.init(agent, team, parameter["nearest_cover"]);
    }
    return result;
}
