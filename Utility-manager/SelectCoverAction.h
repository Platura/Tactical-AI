#pragma once
#include "IAction.h"
#include "BlackboardAddr.h"
class SelectCoverAction :
    public IAction
{
    //Action for selecting a Cover to move to
private:
	BlackboardAddr m_hidden_cover;
	BlackboardAddr m_nearest_cover;
	BlackboardAddr m_best_cover;
	BlackboardAddr m_win_cover;
	BlackboardAddr m_movement_map;
	aiPosition nearest_cover;
	aiPosition best_cover;
	TacticalMap cover_efficiency;
	TacticalMap cover_cost;
	TacticalMap cover_win;
	TacticalMap movement_map;
public:

	void onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput*) override;
	void onActionUpdate(BlackboardManager& bm, IEngineDataOutput*) override;
	void onActionFinished(BlackboardManager& bm, IEngineDataOutput*) override;
	static std::unique_ptr<IAction> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);

};

