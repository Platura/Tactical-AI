#pragma once
#include "IConsideration.h"
#include "BlackboardAddr.h"

class ThreatConsideration : public IConsideration
{
	BlackboardAddr m_value;
	BlackboardAddr m_position;
	
public:
	ThreatConsideration();
	float compute(BlackboardManager& bm) override;
	static std::unique_ptr<IConsideration> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);
};


