#pragma once
#include "IAction.h"
#include "BlackboardAddr.h"
class TakeAimAction :
    public IAction
{
    BlackboardAddr m_direction;
    float delta_rotation;
    float agent_rotation;
    float angle;
    float delta_time = 0;
    float rot_direction = 1;
public:
    void onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput*) override;
    void onActionUpdate(BlackboardManager& bm, IEngineDataOutput*) override;
    void onActionFinished(BlackboardManager& bm, IEngineDataOutput*) override;

    static std::unique_ptr<IAction> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);

    static float clamp_rotation(float rot);
};

