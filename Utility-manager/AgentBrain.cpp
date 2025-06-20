#include "AgentBrain.h"
#include <fmt/format.h>
#include <imgui.h>
AgentBrain::AgentBrain(aiAgentId i, IReasoner::ptr ptr) :
	id(i),
	m_reasoner(std::move(ptr))
{
}

void AgentBrain::reset()
{
}

void AgentBrain::update()
{
}

void AgentBrain::think(BlackboardManager& bm, IEngineDataOutput* cmd)
{
	if (!m_reasoner)
	{
		return;
	}

	if (is_running_action && !m_reasoner->getOption(m_current_option).isInterruptible())
		return;

	m_reasoner->update(bm);

	auto selection = m_reasoner->getSelectedOptionId();

	if (selection != m_current_option)
	{
		if (m_current_option != std::numeric_limits<size_t>::max())
		{
			auto& option = m_reasoner->getOption(m_current_option);

			if(m_current_action != option.getActionEnd())
				m_current_action->get()->onActionFinished(bm, cmd);
		}

		m_current_option = selection;
		m_current_action = m_reasoner->getOption(m_current_option).getActionEnd();
		
	}

}

void AgentBrain::act(BlackboardManager& bm, IEngineDataOutput* cmd, IEngineDataInput* data)
{
	if (m_current_option == std::numeric_limits<size_t>::max() || !m_reasoner)
		return;

	auto& option = m_reasoner->getOption(m_current_option);

	if (m_current_action == option.getActionEnd())
	{
		// Action gerade gestarted
		m_current_action = option.getActionsBegin();
		if (m_current_action == option.getActionEnd())
			return;
		m_current_action->get()->onActionStart(bm, cmd, data);
		fmt::print("[Brain {}] Starting Option {} with action {}\n", id, option.getName(), m_current_action->get()->getName());
		is_running_action = true;
	}

	m_current_action->get()->onActionUpdate(bm, cmd);

	if (m_current_action->get()->isFinished())
	{
		m_current_action->get()->onActionFinished(bm, cmd);
		m_current_action->get()->setisFinished(false);
		fmt::print("[Brain {}] Option {} Ending action {}\n", id, option.getName(), m_current_action->get()->getName());


		++m_current_action;

		if (m_current_action == option.getActionEnd())
		{
			fmt::print("[Brain {}] Ending Option {}\n", id, option.getName());
			is_running_action = false;
			m_current_option = std::numeric_limits<size_t>::max();
			return;
		}

		fmt::print("[Brain {}] Option {} Starting action {}\n", id, option.getName(), m_current_action->get()->getName());

		m_current_action->get()->onActionStart(bm, cmd, data);
	}

}

void AgentBrain::DrawDebug()
{
	if (m_reasoner)
	{
		
		if (!(m_current_option == std::numeric_limits<size_t>::max()))
		{
			auto& option = m_reasoner->getOption(m_current_option);

			auto const aktion_cout = option.getActionCount();
			auto const current = m_current_action - option.getActionsBegin();

			ImGui::Text(fmt::format("Current Option: {}", option.getName()).c_str());
			ImGui::Text(fmt::format("Current Aktion ({}/{}) {})", current, aktion_cout, m_current_action->get()->getName()).c_str());
		}
		m_reasoner->drawDebug();
	}
}
