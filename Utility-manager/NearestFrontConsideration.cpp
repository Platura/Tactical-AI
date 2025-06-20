#include "NearestFrontConsideration.h"

NearestFrontConsideration::NearestFrontConsideration()
{
}

float NearestFrontConsideration::compute(BlackboardManager& bm)
{
    auto& agent_bb = bm.getAgentBlackboard(m_agent);
    auto& team_bb = bm.getTeamBlackboard(m_team);

    auto front_map_opt = team_bb.getValue<TacticalMap>("front_map");
    if (!front_map_opt.has_value())
        return 0.0f;

    auto front_map = front_map_opt.value();
    auto current_front = front_map.getMaxValue();

    auto target_front_opt = agent_bb.getValue<aiPosition>("front_target");

    // Check if we need to assign a new front target
    bool needs_new_target = true;

    if (target_front_opt.has_value()) {
        auto target_front = target_front_opt.value();
        float dx = std::abs(current_front.x - target_front.x);
        float dy = std::abs(current_front.y - target_front.y);
        float distance = dx + dy;

        if (distance >= 2.0f) {
            // Keep using current target
            needs_new_target = false;

            // Normalize distance for utility
            float normalized = 1- std::clamp(distance / max_distance, 0.0f, 1.0f);
            return normalized;
        }
    }
}

std::unique_ptr<IConsideration> NearestFrontConsideration::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
    auto result = std::make_unique<NearestFrontConsideration>();
    return result;
}
