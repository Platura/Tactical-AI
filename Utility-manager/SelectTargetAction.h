#pragma once
#include "IAction.h"
#include "BlackboardAddr.h"

//Selects an enemy target
class SelectTargetAction :
    public IAction
{
private:
	//preset enemy target used for testing, can be set in the json
	BlackboardAddr m_agent_target;
	aiAgentId agent_target_id;
public:

	void onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput*) override;
	void onActionUpdate(BlackboardManager& bm, IEngineDataOutput*) override;
	void onActionFinished(BlackboardManager& bm, IEngineDataOutput*) override;

	static std::unique_ptr<IAction> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);
};

