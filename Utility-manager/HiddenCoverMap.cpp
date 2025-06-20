#include "HiddenCoverMap.h"
#include "Costfield.h"
#include <vector>

TacticalMap HiddenCoverMap::compute(TacticalMap cover_map, TacticalMap global_vis)
{
    TacticalMap tm;
    tm = cover_map * global_vis.invert();
    return tm;
}

TacticalMap HiddenCoverMap::computeAverageEfficiency(TacticalMap& hidden_cover, std::vector<std::pair<uint32_t, uint32_t>> cover)
{
    int filled = 0;
    float cover_eval = 0;
    TacticalMap cover_efficiency;
    cover_efficiency.init(hidden_cover.getSizeX(), hidden_cover.getSizeY(), 0.f);
    for (auto const& el : cover)
    {
        int x = el.first;
        int y = el.second;
        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {
                if (x + i < hidden_cover.getSizeX() && y + j < hidden_cover.getSizeY()) {
                    if (hidden_cover.at(x + i, y + j) > 0.f)
                    {
                        cover_eval += hidden_cover.at(x + i, y + j);
                        filled++;
                    }
                }
            }
        }
        cover_efficiency.at(x, y) = cover_eval / filled;
        cover_eval = 0;
        filled = 0;
    }
    return cover_efficiency;
}

TacticalMap HiddenCoverMap::computeAverageCost(TacticalMap movement_map, std::vector<std::pair<uint32_t, uint32_t>> cover)
{
    int filled = 0;
    float cover_eval = 0;
    TacticalMap cover_cost;
    cover_cost.init(movement_map.getSizeX(), movement_map.getSizeY(), 0.f);
    for (auto const& el : cover)
    {
        int x = el.first;
        int y = el.second;
        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {
                if (x + i < movement_map.getSizeX() && y + j < movement_map.getSizeY()) {
                    if (movement_map.at(x + i, y + j) > 0.f && movement_map.at(x + i, y + j) < 200)
                    {
                        cover_eval += movement_map.at(x + i, y + j);
                        filled++;
                        if (movement_map.at(x + i, y + j) > m_max_cost && movement_map.at(x + i, y + j)<200)
                            m_max_cost = movement_map.at(x + i, y + j);
                    }
                }
            }
        }
        cover_cost.at(x, y) = cover_eval / filled;
        cover_eval = 0;
        filled = 0;
    }
    return cover_cost;
}


