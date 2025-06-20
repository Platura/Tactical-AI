#include "MovementMap.h"
#include <list>
#include <vector>

TacticalMap MovementMap::compute(aiPosition pos, Costfield cmap)
{
	TacticalMap tm(cmap.getData().getSizeX(), cmap.getData().getSizeY(), std::numeric_limits<float>::max());
	m_flowField.init(cmap.getData().getSizeX(), cmap.getData().getSizeY());
	std::list<uint32_t> open;

	aiPosition agent_pos = { pos.x / 32, pos.y / 32 };
	auto targetIndex = m_flowField.getIndex(agent_pos.x, agent_pos.y);
	tm.at(agent_pos.x, agent_pos.y) = 0;
	m_savedTargets.push_back({ targetIndex, cmap.getData().at(agent_pos.x, agent_pos.y) });
	open.push_back(targetIndex);

	auto width = m_flowField.getSizeX();
	auto height = m_flowField.getSizeY();

	while (!open.empty()) {
		auto cellIndex = open.front();
		open.pop_front();
		auto& cell = tm.getValue(cellIndex);
		auto position = tm.getPosition(cellIndex);


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
				auto& nextCell = cmap.getData().at(x, y);
				if (nextCell == 255)
				{
					continue;
				}
				auto temporaryInteg = cell + nextCell;
				if (temporaryInteg < tm.at(x, y))
				{
					tm.at(x, y) = temporaryInteg;
					open.push_back(m_flowField.getIndex(x, y));
				}
			}
		}
	}
	return tm;
}

