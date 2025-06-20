#include "CoverMap.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

CoverMap::CoverMap()
{
}

void CoverMap::init(uint32_t tiles_x, uint32_t tiles_y, uint32_t tile_size_x, uint32_t tile_size_y)
{
	
}

TacticalMap CoverMap::compute(Costfield& cmap)
{
	TacticalMap tm;
	tm.init(cmap.getData().getSizeX(), cmap.getData().getSizeY(), 0.f);
	for (auto x = 0u; x < tm.getSizeX(); x++)
	{
		for (auto y = 0u; y < tm.getSizeY(); y++)
		{
			if (cmap.getData().at(x, y) == 250)
			{
				addTemplate(x, y, tm);
				m_unwalkable.emplace_back(x, y);
				m_cover.emplace_back(x, y);
			}
			if (cmap.getData().at(x, y) == 255)
			{
				m_unwalkable.emplace_back(x, y);
			}
		}
	}

	for (auto const& el : m_unwalkable)
	{
		tm.at(el.first, el.second) = 0;
	}
	return tm;
}

void CoverMap::addTemplate(int x, int y, TacticalMap& tm)
{
	int index = 0;
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			if (x + i < tm.getSizeX() && y + j < tm.getSizeY()) {
				tm.at(x + i,y + j) = std::max(m_smaler_template.at(index), tm.at(x + i, y + j));
				index++;
			}
		}
	}
}