#include "SelectCoverAction.h"
#include "CoverMap.h"
#include "HiddenCoverMap.h"
#include "MovementMap.h"
#include "../AI-manager/MathHelpers.h"

void SelectCoverAction::onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput*data)
{
	//sets the best cover as position_target
	TacticalMap cover_map;
	std::vector<std::pair<uint32_t, uint32_t>> covers;
	TacticalMap cover = bm.getGlobal().getValue<TacticalMap>("cover").value();
	
	HiddenCoverMap hidden_cover;
	auto cmap = data->getCostField();
	auto global_vis = bm.getGlobal().getValue<TacticalMap>("global_vis").value();
	aiPosition agent_pos = bm.getAgentBlackboard(m_agent).getValue<aiPosition>("position").value();
	MovementMap movement;
	cover_map = hidden_cover.compute(cover, global_vis);
	covers = bm.getGlobal().getValue<std::vector<std::pair<uint32_t, uint32_t>>>("covers").value();
	cover_efficiency = hidden_cover.computeAverageEfficiency(cover_map, covers);
	movement_map = movement.compute(agent_pos, cmap);
	cover_cost = hidden_cover.computeAverageCost(movement_map, covers);

	
	float best_score = 0;
	float w1 = 0.7;
	//weight cover_efficiency and cover_cost
	//cover_efficiency *= w1;
	cover_cost /= 10;
	//cover_cost *= (1 - w1);
	
	cover_win = cover_efficiency / (cover_cost* cover_cost);
	best_cover = cover_win.getMaxValue();
	float best_value = cover_win.at((int)best_cover.x, (int)best_cover.y);

	if (best_value <= 0.01f) 
	{
		//No valid cover
		return;
	}
	auto cover_direction = data->getAgentDirection(m_agent);
	
	bm.getAgentBlackboard(m_agent).setValue<aiPosition>("position_target", { (best_cover.x + cover_direction.x)*32, (best_cover.y + cover_direction.y)*32 });

	
}

void SelectCoverAction::onActionUpdate(BlackboardManager& bm, IEngineDataOutput*)
{
	m_isFinished = true;
}

void SelectCoverAction::onActionFinished(BlackboardManager& bm, IEngineDataOutput*)
{
	*m_win_cover.getPtr<TacticalMap>(bm) = cover_win;
	*m_hidden_cover.getPtr<TacticalMap>(bm) = cover_efficiency;
	*m_movement_map.getPtr<TacticalMap>(bm) = movement_map;
	*m_nearest_cover.getPtr<aiPosition>(bm) = nearest_cover;
	*m_best_cover.getPtr<aiPosition>(bm) = best_cover;
}

std::unique_ptr<IAction> SelectCoverAction::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<SelectCoverAction>();

	if (parameter.contains("win_cover"))
	{
		result->m_win_cover.init(agent, team, parameter["win_cover"]);
	}

	if (parameter.contains("movement_map"))
	{
		result->m_movement_map.init(agent, team, parameter["movement_map"]);
	}

	if (parameter.contains("best_cover"))
	{
		result->m_best_cover.init(agent, team, parameter["best_cover"]);
	}

	if (parameter.contains("nearest_cover"))
	{
		result->m_nearest_cover.init(agent, team, parameter["nearest_cover"]);
	}

	if (parameter.contains("hidden_cover"))
	{
		result->m_hidden_cover.init(agent, team, parameter["hidden_cover"]);
	}

	return result;
}
