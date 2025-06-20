#include "SelectPositionAction.h"
#include <ctime>
#include <cstdlib>

void SelectPositionAction::onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput*)
{
	TacticalMap ambush = bm.getAgentBlackboard(m_agent).getValue<TacticalMap>("ambush").value();
	auto target_id = bm.getAgentBlackboard(m_agent).getValue<aiAgentId>("agent_target").value();
	auto agent_target_pos = bm.getAgentBlackboard(target_id).getValue<aiPosition>("position").value();
	auto shoot_distance = 5.f;
	
	agent_target_pos.x /= 32;
	agent_target_pos.y /= 32;
	uint32_t trys = 0;
	while (true)
	{
		target_pos = selectRandomPoint(ambush, shoot_distance, agent_target_pos);
		if (ambush.at(int(target_pos.x), (int)target_pos.y) == 1.f)
		{
			target_pos.x *= 32;
			target_pos.y *= 32;
			break;
		}

		if (trys++ >= 50)
		{
			target_pos.x *= 32;
			target_pos.y *= 32;
			fmt::print("No Valid Point found\n");
			break;
		}
	}
	
}

void SelectPositionAction::onActionUpdate(BlackboardManager& bm, IEngineDataOutput*)
{
	m_isFinished = true;
}

void SelectPositionAction::onActionFinished(BlackboardManager& bm, IEngineDataOutput*)
{
	*m_position_target.getPtr<aiPosition>(bm) = target_pos;
}

aiPosition SelectPositionAction::selectRandomPoint(TacticalMap& am, double r, aiPosition start)
{
	double angle = (rand() / (double)RAND_MAX) * 2 * 3.14;
	double radius = sqrt((rand() / (double)RAND_MAX) * r * r);
	aiPosition p;
	p.x = start.x + radius * cos(angle);
	p.y = start.y + radius * sin(angle);
	return p;
}

std::unique_ptr<IAction> SelectPositionAction::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<SelectPositionAction>();

	if (parameter.contains("position_target"))
	{
		result->m_position_target.init(agent, team, parameter["position_target"]);
	}

	return result;
}
