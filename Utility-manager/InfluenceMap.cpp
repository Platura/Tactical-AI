#include "InfluenceMap.h"
#include <iostream>
#include <iomanip>

InfluenceMap::InfluenceMap()
{
}

void InfluenceMap::init(uint32_t tiles_x, uint32_t tiles_y, uint32_t tile_size_x, uint32_t tile_size_y)
{
	m_threat_map_max.init(tiles_x, tiles_y);
	m_threat_map_sum.init(tiles_x, tiles_y);
	m_save_points.init(tiles_x, tiles_y);
	m_tile_size_x = tile_size_x;
	m_tile_size_y = tile_size_y;
}

void InfluenceMap::compute(std::vector<AgentEntity> const& entities, const Costfield& cmap)
{
	for (int i = 0; i < entities.size(); i++)
	{
		int enty_cell_x = entities[i].pos.x / m_tile_size_x;
		int enty_cell_y = entities[i].pos.y / m_tile_size_y;

		auto& current_template = m_linear_templates[entities[i].type];

		int half_template_x = current_template.getSizeX() / 2;
		int half_template_y = current_template.getSizeY() / 2;


		for (auto x = 0; x < current_template.getSizeX(); ++x)
		{
			for (auto y = 0; y < current_template.getSizeY(); ++y)
			{
				int map_x = enty_cell_x + (x - half_template_x);
				int map_y = enty_cell_y + (y - half_template_y);
				if (map_x < 0 || map_y < 0 || map_x >= m_threat_map_max.getSizeX() || map_y >= m_threat_map_max.getSizeY())
					continue;
				// Obstacle check: skip if path from entity to cell is obstructed
				if (isObstructed(enty_cell_x, enty_cell_y, map_x, map_y, cmap))
				{
					if (cmap.getData().at(map_x, map_y) == 255)
						continue;
					if (current_template.at(x, y) == 0)
						continue;
					m_save_points.at(map_x,map_y) = 1;
					continue;
				}
					
				// Map with max()
				m_threat_map_max.at(map_x, map_y) = std::max(current_template.at(x, y), m_threat_map_max.at(map_x, map_y));
				// Map with sum
				m_threat_map_sum.at(map_x, map_y) += current_template.at(x, y);
			}
		}
	}
	//consoleOut(m_threat_map);
}

bool InfluenceMap::isObstructed(int x0, int y0, int x1, int y1, const Costfield& cmap)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (true)
	{
		if (cmap.getData().at(x0, y0) == 255)
			return true;

		if (x0 == x1 && y0 == y1)
			break;

		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}

	return false;
}

void InfluenceMap::createExpoTemplate(uint32_t type, float distance)
{
}

void InfluenceMap::consoleOut(Field<float> field)
{
	for (int y = 0; y < field.getSizeY(); y++)
	{
		for (int x = 0; x < field.getSizeX(); x++)
		{
			std::cout << std::setw(4) << std::setprecision(2)
				<< std::setfill('0') << field.at(x, y) << ", ";
		}
		std::cout << std::endl;
	}
}

float InfluenceMap::at(float x, float y) const
{
	uint32_t xx = x / m_tile_size_x;
	uint32_t yy = y / m_tile_size_y;

	return m_threat_map_max.at(xx, yy);
}

void InfluenceMap::createLinearTemplate(uint32_t type, float distance)
{
	Field<float> temp;
	temp.init(distance * 2, distance * 2);
	int center = distance;
	for (int x = 0; x < temp.getSizeX(); x++)
	{
		for (int y = 0; y < temp.getSizeY(); y++)
		{
			float vec_x = center - x;
			float vec_y = center - y;

			float current_distance = sqrt(vec_x * vec_x + vec_y * vec_y);

			if (current_distance > distance)
			{
				temp.at(x, y) = 0.f;
			}
			else
			{
				temp.at(x, y) = 1.f -( current_distance / distance);
				
			}
		}
	}
	m_linear_templates.insert({ type, temp });
	//consoleOut(temp);
}
