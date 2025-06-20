
#pragma once
#include "IAction.h"
#include "BlackboardAddr.h"
class ReloadAction :
    public IAction
{

	BlackboardAddr m_ammunition;
	int ammo;

public:
	void onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput*) override;
	void onActionUpdate(BlackboardManager& bm, IEngineDataOutput*) override;
	void onActionFinished(BlackboardManager& bm, IEngineDataOutput*) override;

	static std::unique_ptr<IAction> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);
};

