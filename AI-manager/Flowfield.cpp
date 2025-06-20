#include "Flowfield.h"
#include <list>
#include <iostream>
#include <cmath>

Flowfield::Flowfield()
{
}

void Flowfield::init(Field<int> const& tilemap, Field<uint32_t> const& costmap, sf::Vector2f const& tile_size)
{
	m_flowField.init(tilemap.getSizeX(), tilemap.getSizeY());
	m_costField = costmap;
	m_tile_size = tile_size;
}

void Flowfield::integrate(std::vector<sf::Vector2i> const& targets)
{
	resetIntegration();
	std::list<uint32_t> open;
	for (auto const& t : targets)
	{
		auto targetIndex = m_flowField.getIndex(t.x, t.y);
		m_integrationField.at(t.x, t.y) = 0;
		m_savedTargets.push_back({ targetIndex, m_costField.at(t.x,t.y) });
		open.push_back(targetIndex);
	}
	auto width = m_flowField.getSizeX();
	auto height = m_flowField.getSizeY();

	while (!open.empty()) {
		auto cellIndex = open.front();
		open.pop_front();
		auto& cell = m_integrationField.getValue(cellIndex);
		auto position = m_integrationField.getPosition(cellIndex);


		for (auto iy = -1; iy <= 1; ++iy)
		{
			for (auto ix = -1; ix <= 1; ++ix)
			{
				int x = position.x + ix;
				int y = position.y + iy;
				if (x < 0 || y < 0 || y >= height || x >= width)
				{
					continue;
				}
				auto& nextCell = m_costField.at(x,y);
				if (nextCell == 255)
				{
					continue;
				}
				auto temporaryInteg = cell + nextCell;
				if (temporaryInteg < m_integrationField.at(x, y))
				{
					m_integrationField.at(x, y) = temporaryInteg;
					open.push_back(m_flowField.getIndex(x,y));
				}
			}
		}
	}
	computeDirection();
}

void Flowfield::computeDirection()
{
	auto width = m_flowField.getSizeX();
	auto height = m_flowField.getSizeY();
	for (int i = 0; i < height * width; ++i) {
		auto currentCell = m_integrationField.getPosition(i);
		auto currentInteg = m_integrationField.getValue(i);

		m_flowField.at(i) = sf::Vector2f(0, 0);
		for (auto iy = -1; iy <= 1; ++iy)
		{
			for (auto ix = -1; ix <= 1; ++ix)
			{
				int x = currentCell.x + ix;
				int y = currentCell.y + iy;
				if (x < 0 || y < 0 || y >= height || x >= width)
				{
					continue;
				}
				if (currentInteg < m_integrationField.at(x, y))
				{
					continue;
				}
				currentInteg = m_integrationField.at(x, y);

				float length = std::sqrt(ix * ix + iy * iy);

				if (length == 0)
				{
					continue;
				}
				m_flowField.at(i) = sf::Vector2f{ix / length, iy / length } ;
				
			}
		}
	}
}

sf::Vector2f Flowfield::getAtWorldPos(sf::Vector2f pos) const
{
	if (m_flowField.getSize() == 0)
		return { 0,0 };

	sf::Vector2i grid_pos = worldToGridPos(pos);

	return m_flowField.at(grid_pos.x, grid_pos.y);
}

sf::Vector2i Flowfield::worldToGridPos(sf::Vector2f world_pos) const
{
	auto const size_x = m_flowField.getSizeX();
	auto const size_y = m_flowField.getSizeY();

	auto x = std::clamp<int>(std::floor(world_pos.x / m_tile_size.x), 0, size_x - 1);
	auto y = std::clamp<int>(std::floor(world_pos.y / m_tile_size.y), 0, size_y - 1);

	return { x,y };
}

bool Flowfield::isPosAtTarget(sf::Vector2f from) const
{
	auto grid_pos = worldToGridPos(from);
	return grid_pos.x == m_savedTargets[0].first && grid_pos.y == m_savedTargets[0].second;
}


void Flowfield::resetIntegration()
{
	m_integrationField.init(m_costField.getSizeX(), m_costField.getSizeY(), std::numeric_limits<float>::max());
}
