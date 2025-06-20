#include "..\Utility-manager\ReloadAction.h"

void ReloadAction::onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput*)
{
	aiInt max_ammunition = bm.getGlobal().getValue<aiInt>("max_ammunition").value();
	ammo = max_ammunition;
}

void ReloadAction::onActionUpdate(BlackboardManager& bm, IEngineDataOutput*cmd)
{
	cmd->reload(m_agent);
	m_isFinished = true;
}

void ReloadAction::onActionFinished(BlackboardManager& bm, IEngineDataOutput*)
{
	*m_ammunition.getPtr<aiInt>(bm) = ammo;
}

std::unique_ptr<IAction> ReloadAction::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<ReloadAction>();

	if (parameter.contains("ammunition"))
	{
		result->m_ammunition.init(agent, team, parameter["ammunition"]);
	}

	return result;
}
