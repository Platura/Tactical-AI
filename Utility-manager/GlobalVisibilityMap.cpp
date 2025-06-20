#include "GlobalVisibilityMap.h"
#include <algorithm>

GlobalVisibilityMap::GlobalVisibilityMap()
{
}

void GlobalVisibilityMap::init(uint32_t tiles_x, uint32_t tiles_y, uint32_t tile_size_x, uint32_t tile_size_y)
{
	//m_global_visibility.init(tiles_x, tiles_y);
	m_tile_size_x = tile_size_x;
	m_tile_size_y = tile_size_y;
}

TacticalMap GlobalVisibilityMap::compute(Costfield &cmap)
{
	TacticalMap tm;
	tm.init(cmap.getData().getSizeX(), cmap.getData().getSizeY(), 0.f);
	float max = 0;
	for (int x = 0; x < tm.getSizeX(); x++)
	{
		for (int y = 0; y < tm.getSizeY(); y++)
		{
			auto score = scoreCell(cmap,{x,y}, tm);
			max = std::max(max, score);
			tm.at(x, y) = score;
		}
	}

	for (int x = 0; x < tm.getSizeX(); x++)
	{
		for (int y = 0; y < tm.getSizeY(); y++)
		{
			tm.at(x, y) = tm.at(x, y) / max;
		}
	}
	return tm;
}

float GlobalVisibilityMap::scoreCell(Costfield &cmap, VecInt2D start, TacticalMap&tm)
{
	float score = 0;
	for (int x = 0; x < tm.getSizeX(); x+=iteration_step_size)
	{
		for (int y = 0; y < tm.getSizeY(); y+=iteration_step_size)
		{
			if (checkLOS(cmap,start, { x,y }, tm))
			{
				score += 1.f;
			}
		}
	}
	return score;
}

bool GlobalVisibilityMap::checkLOS(Costfield &cmap, VecInt2D start, VecInt2D end, TacticalMap& tm)
{
	auto deltaX = std::abs(start.x - end.x);
	auto deltaY = std::abs(start.y - end.y);

	auto dirX = start.x < end.x ? 1 : -1;
	auto dirY = start.y < end.y ? 1 : -1;

	bool swap = false;
	if (deltaX < deltaY)
	{
		swap = true;
		std::swap(deltaX, deltaY);
		std::swap(dirX, dirY);
	}
	auto currentPos = start;
	auto e = 2 * deltaY - deltaX;

	//start has 255 cost
	if (cmap.getData().at(currentPos.x,currentPos.y)==255)
		return false;

	while (currentPos.x != end.x && currentPos.y != end.y)
	{
		if (e <= 0)
		{
			if (!swap)
			{
				currentPos.x += dirX;
			}
			else {
				currentPos.y += dirX;
			}
			e += 2 * deltaY;
		}
		else {
			if (!swap)
			{
				currentPos.x += dirX;
				currentPos.y += dirY;
			}
			else
			{
				currentPos.y += dirX;
				currentPos.x += dirY;
			}
			e += 2 * deltaY - 2 * deltaX;
		}
		if (currentPos.x < 0 || currentPos.y < 0 || currentPos.x >= tm.getSizeX() || currentPos.y >= tm.getSizeY())
		{
			break;
		}

		if (cmap.getData().at(currentPos.x, currentPos.y) == 255)
			return false;
	}
	return true;
}
