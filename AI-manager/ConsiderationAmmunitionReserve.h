#pragma once
#include "IConsideration.h"
#include <imgui.h>
#include "Agent.h"


class ConsiderationAmmunitionReserve :
	public IConsideration
{
	Agent* m_agent;
	int m_currentAmmo = 0;
	int m_maxAmmo = 0;
	float m_k = 0.2;
public:
	ConsiderationAmmunitionReserve(Agent* a);
	float compute(BlackboardManager& bm) override;
	void DrawDebugUiChild() override;
};

