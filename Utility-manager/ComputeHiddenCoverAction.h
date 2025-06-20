#pragma once
#include "IAction.h"
#include "BlackboardAddr.h"

class ComputeHiddenCoverAction :
    public IAction
{
	//Action for computing cover values that can be used for movement
private:
	BlackboardAddr m_cover;
	TacticalMap cover_map;
public:

	void onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput*) override;
	void onActionUpdate(BlackboardManager& bm, IEngineDataOutput*) override;
	void onActionFinished(BlackboardManager& bm, IEngineDataOutput*) override;

	static std::unique_ptr<IAction> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);

};

