#pragma once
#include "TacticalMap.h"
class HiddenCoverMap
{
public:
	//Map that combines the global Visibility with the Covermap
	HiddenCoverMap() = default;
	TacticalMap compute(TacticalMap cover_map, TacticalMap global_vis);
	TacticalMap computeAverageEfficiency(TacticalMap& hidden_cover, std::vector<std::pair<uint32_t, uint32_t>> cover);
	TacticalMap computeAverageCost(TacticalMap movement_map, std::vector<std::pair<uint32_t, uint32_t>> cover);
	float getMaxCost() {
		return m_max_cost;
	}
private:
	float m_max_cost=0;
};

