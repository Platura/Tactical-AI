#include "SelectHoldAction.h"
#include "InfluenceMap.h"

void SelectHoldAction::action(BlackboardManager& bm)
{
	auto save_map=bm.getGlobal().getValue<TacticalMap>("save_map");
	auto front_id=bm.getAgentBlackboard(m_agent).getValue<aiAgentId>("front_agent");
	if (!front_id.has_value())
		return;
	auto pos_opt = bm.getAgentBlackboard(front_id.value()).getValue<aiPosition>("position");
	if (!pos_opt.has_value())
		return; 
	auto front_pos = pos_opt.value();
	int front_cell_x = front_pos.x / 32;
	int front_cell_y = front_pos.y / 32;
	int range = 5;

	std::vector<std::pair<int, int>> candidates;

	for (int x = 0; x < save_map.value().getSizeX(); ++x)
	{
		for (int y = 0; y < save_map.value().getSizeY(); ++y)
		{
			if (save_map.value().at(x, y) == 1)
			{
				int dx = x - front_cell_x;
				int dy = y - front_cell_y;
				int dist_squared = dx * dx + dy * dy;

				if (dist_squared <= range * range)
				{
					candidates.emplace_back(x, y);
				}
			}
		}
	}
	if (!candidates.empty())
	{
		int random_index = rand() % candidates.size();
		auto [cell_x, cell_y] = candidates[random_index];

		aiPosition pos;
		pos.x = cell_x * 32 + 32 / 2;
		pos.y = cell_y * 32 + 32 / 2;
		bm.getAgentBlackboard(m_agent).setValue("position_target", pos);
	}
	bm.getAgentBlackboard(m_agent).setValue("position_target", front_pos);
}

std::unique_ptr<IAction> SelectHoldAction::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<SelectHoldAction>();

	return result;
}
