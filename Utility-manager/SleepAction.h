#pragma once
#include "IAction.h"
#include <chrono>

class SleepAction :
    public IAction
{
    int64_t m_sleep_time;

    std::chrono::high_resolution_clock::time_point m_start;
public:

    void onActionStart(BlackboardManager& bm, IEngineDataOutput*, IEngineDataInput*) ;
    void onActionUpdate(BlackboardManager& bm, IEngineDataOutput*) ;
    void onActionFinished(BlackboardManager& bm, IEngineDataOutput*) ;

    static std::unique_ptr<IAction> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);

};

