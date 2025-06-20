#pragma once
#include "IConsideration.h"
#include "Agent.h"
#include "imgui.h"
class ConsiderationEnemyDistance :
    public IConsideration
{
    Agent* agent;
    float m_enemyDistance=3.f;
public:
    ConsiderationEnemyDistance();
    float compute(BlackboardManager& bm) override;
    void DrawDebugUiChild() override;
};

