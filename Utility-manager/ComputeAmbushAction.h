#pragma once
#include "IAction.h"
#include "BlackboardAddr.h"
#include "IEngineDataInput.h"
#include "AmbushMap.h"
class ComputeAmbushAction :
    public IAction
{
	BlackboardAddr m_ambush_map;
	aiPosition ambush_map;
	TacticalMap compute_ambush;

public:

	void onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput* data) override;
	void onActionUpdate(BlackboardManager& bm, IEngineDataOutput*) override;
	void onActionFinished(BlackboardManager& bm, IEngineDataOutput*) override;

	static std::unique_ptr<IAction> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);

};

