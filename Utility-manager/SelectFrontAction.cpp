#include "SelectFrontAction.h"
#include "SaveFrontMap.h"

void SelectFrontAction::action(BlackboardManager& bm)
{
	auto current_front = bm.getTeamBlackboard(m_team).getValue<TacticalMap>("front_map");
	bm.getAgentBlackboard(m_agent).setValue<aiPosition>("position_target", bm.getAgentBlackboard(m_agent).getValue<aiPosition>("position").value());
	if (!current_front.has_value())
	{
		return;
	}
	auto spotted_map = bm.getGlobal().getValue<TacticalMap>("combined_vis");
	auto cover_map = bm.getGlobal().getValue<TacticalMap>("cover");
	if (!spotted_map.has_value() || !cover_map.has_value())
	{
		return;
	}
	auto front_cell = current_front.value().getMaxValue();
	bm.getAgentBlackboard(m_agent).setValue("front_target", front_cell);
	SaveFrontMap save_front;
	TacticalMap save_spot = save_front.compute(front_cell, cover_map.value(), spotted_map.value());
	auto save_spot_max = save_spot.getMaxValue();
	if (save_spot_max.x != 0 || save_spot_max.y != 0)
	{
		bm.getAgentBlackboard(m_agent).setValue<aiPosition>("position_target", { save_spot_max.x * 32,save_spot_max.y * 32 });
		return;
	}
	else
	{
		bm.getAgentBlackboard(m_agent).setValue<aiPosition>("position_target", { front_cell.x * 32, front_cell.y * 32 });
	}


	
}

std::unique_ptr<IAction> SelectFrontAction::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<SelectFrontAction>();
	return result;
}

