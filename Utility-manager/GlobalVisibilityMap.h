#pragma once
#include "Types.hpp"
#include "Costfield.h"
#include "Field.h"
#include "TacticalMap.h"
class GlobalVisibilityMap
{
	//A map that contains the visibility of every point from every point
public:
	GlobalVisibilityMap();
	void init(uint32_t tiles_x, uint32_t tiles_y, uint32_t tile_size_x, uint32_t tile_size_y);
	TacticalMap compute(Costfield &cmap);
	float scoreCell(Costfield &cmap, VecInt2D start, TacticalMap& tm);
	bool checkLOS(Costfield &cmap, VecInt2D start, VecInt2D end, TacticalMap& tm);

private:
	int m_tile_size_x;
	int m_tile_size_y;
	int iteration_step_size = 1;
};

