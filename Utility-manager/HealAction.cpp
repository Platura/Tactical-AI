#include "HealAction.h"

void HealAction::action(BlackboardManager& bm)
{
	auto current_hp=bm.getAgentBlackboard(m_agent).getValue<aiInt>("current_hp").value();
	if(current_hp<100)
		bm.getAgentBlackboard(m_agent).setValue("current_hp", current_hp++);
}

std::unique_ptr<IAction> HealAction::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<HealAction>();

	return result;
}
