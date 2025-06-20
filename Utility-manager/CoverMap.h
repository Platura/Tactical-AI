#pragma once
#include "TacticalMap.h"
#include "GlobalVisibilityMap.h"
#include "Types.hpp"
#include "Field.h"
#include <vector>
class CoverMap
{
public:
	CoverMap();
	void init(uint32_t tiles_x, uint32_t tiles_y, uint32_t tile_size_x, uint32_t tile_size_y);
	TacticalMap compute(Costfield& cmap);
	void addTemplate(int x, int y, TacticalMap& tm);
	std::vector<std::pair<uint32_t, uint32_t>> getCover()
	{
		return m_cover;
	}
private:
	std::vector<std::pair<uint32_t, uint32_t>> m_cover;
	std::vector<std::pair<uint32_t, uint32_t>> m_unwalkable;
	int template_size = 5;
	std::vector<float> m_cover_template = {
		0., 0., 0.5, 0, 0,
		 0, 0.7, 1, 0.7, 0,
		 0.5, 1, 0, 1, 0.5 ,
		 0, 0.7, 1, 0.7, 0 ,
		 0, 0, 0.5, 0, 0 
	};
	std::vector<float> m_smaler_template = {
		 0.7, 0.9, 0.7,
		 0.9, 0, 0.9,
		 0.7, 0.9, 0.7
	};
};

