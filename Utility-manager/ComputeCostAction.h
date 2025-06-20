#pragma once
#include "Costfield.h"
#include "IAction.h"
#include "BlackboardAddr.h"

//Action should modify the costmap so the agents use different routes
class ComputeCostAction :
    public IAction
{
	BlackboardAddr m_mod_cost;
	Costfield m_cost;
public:

	void onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput*) override;
	void onActionUpdate(BlackboardManager& bm, IEngineDataOutput*) override;
	void onActionFinished(BlackboardManager& bm, IEngineDataOutput*) override;

	static std::unique_ptr<IAction> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);

};

