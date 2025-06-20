#pragma once
#include "IAction.h"
#include "BlackboardAddr.h"
class SelectFollowAction :
	public IAction
{
	BlackboardAddr m_front_agent;
	aiAgentId selected_front;
public:

	void onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput*) override;
	void onActionUpdate(BlackboardManager& bm, IEngineDataOutput*) override;
	void onActionFinished(BlackboardManager& bm, IEngineDataOutput*) override;
	static std::unique_ptr<IAction> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);

};



