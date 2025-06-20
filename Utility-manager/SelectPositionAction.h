#pragma once
#include "IAction.h"
#include "BlackboardAddr.h"
class SelectPositionAction :
    public IAction
{
	BlackboardAddr m_position_target;
	aiPosition target_pos;
public:

	void onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput*) override;
	void onActionUpdate(BlackboardManager& bm, IEngineDataOutput*) override;
	void onActionFinished(BlackboardManager& bm, IEngineDataOutput*) override;
	aiPosition selectRandomPoint(TacticalMap& am, double r, aiPosition start);
	static std::unique_ptr<IAction> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);

};

