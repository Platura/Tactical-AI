#pragma once
#include "IConsideration.h"
#include "BlackboardAddr.h"

class DangerConsideration :
    public IConsideration
{
	BlackboardAddr m_value;
	BlackboardAddr m_position;
	int radius = 1;
public:
	DangerConsideration();
	//claculates the average threat around the agent 
	float compute(BlackboardManager& bm) override;
	static std::unique_ptr<IConsideration> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);
};

