#include "IncrementAction.h"
#include <fmt/format.h>
#include <variant>

void IncrementAction::action(BlackboardManager& bm)
{
	auto& v = m_name.getVariant(bm);

	std::visit([](auto&& arg)
		{
			using T = std::decay_t<decltype(arg)>;
			if constexpr (std::is_same_v<T, aiInt> 
					|| std::is_same_v<T, aiUInt> 
				|| std::is_same_v<T, uint64_t>)
				arg += 1;
			else if constexpr (std::is_same_v<T, aiFloat>)
				arg += 1.f;

		}, v);
}

std::unique_ptr<IAction> IncrementAction::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<IncrementAction>();

	if (!parameter.contains("name"))
	{
		fmt::print("[ERROR] BlackboardValueConsideration: missing field value");
		return nullptr;
	}
	else
	{
		result->m_name.init(agent, team, parameter["name"]);
	}


	return result;
}
