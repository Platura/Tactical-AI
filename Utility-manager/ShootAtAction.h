#pragma once
#include "IAction.h"
#include "BlackboardAddr.h"

class ShootAtAction :
    public IAction
{
	BlackboardAddr m_ammunition;
	int ammo;
	Vec2D shot_pos;

public:
	void onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput*) override;
	void onActionUpdate(BlackboardManager& bm, IEngineDataOutput*) override;
	void onActionFinished(BlackboardManager& bm, IEngineDataOutput*) override;

	static std::unique_ptr<IAction> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);
};

