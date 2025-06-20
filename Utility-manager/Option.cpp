#include "Option.h"
#include <imgui.h>

Option::Option(std::string name) : name(name)
{
}

void Option::addConsideration(ConsiderationPtr p_consideration)
{
	considerations.push_back( std::move(p_consideration));
}

void Option::addAction(IAction::ptr&& action)
{
	m_actions.emplace_back(std::move(action));
}

float Option::compute(BlackboardManager& bm)
{
	if (considerations.empty())
		return 0;

	
	float result = 1.f;
	for (auto& c : considerations)
	{
		result *= c->compute_with_weight(bm);
	}
	last_value = result;

	return result;
}

void Option::DrawDebugUi()
{
	ImGui::LabelText("Value", "%f", last_value);
	ImGui::SeparatorText("Considerations:");
	for (auto& c : considerations)
	{
		
		c->DrawDebugUi();
	}
}

