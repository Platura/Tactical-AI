#include "SleepAction.h"

#include <fmt/format.h>

void SleepAction::onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput*)
{
	m_start = std::chrono::high_resolution_clock::now();
}

void SleepAction::onActionUpdate(BlackboardManager& bm, IEngineDataOutput*)
{
	auto time = std::chrono::high_resolution_clock::now() - m_start;

	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(time).count();

	if (seconds >= m_sleep_time)
	{
		setisFinished(true);
	}
}

void SleepAction::onActionFinished(BlackboardManager& bm, IEngineDataOutput*)
{
}

std::unique_ptr<IAction> SleepAction::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<SleepAction>();

	if (!parameter.contains("time"))
	{
		fmt::print("[ERROR] BlackboardValueConsideration: missing field value");
	}
	else
	{
		result->m_sleep_time = parameter["time"];
	}


	return result;
}
