#pragma once
#include "IOneTimeAction.h"
#include "BlackboardAddr.h"
class LookAroundAction :
    public IAction
{
private:
    float rotation;
    float deltaTime;
public:
    void onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput*) override;
    void onActionUpdate(BlackboardManager& bm, IEngineDataOutput*) override;
    void onActionFinished(BlackboardManager& bm, IEngineDataOutput*) override;

    static std::unique_ptr<IAction> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);

    static float clamp_rotation(float rot);
};

