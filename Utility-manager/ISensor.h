#pragma once
#include "BlackboardManager.h"
#include "IEngineDataInput.h"

#include "nlohmann/json.hpp"
using json = nlohmann::json;

class ISensor
{
public:

	virtual void update(BlackboardManager& bm, IEngineDataInput* data) = 0;

	inline void setEntityAndTeam(aiAgentId a, aiTeamId t)
	{
		m_agent = a;
		m_team = t;
	}
	aiAgentId getAgentId() const { return m_agent; }

protected:
	aiAgentId m_agent = NoAgent;
	aiTeamId m_team = NoTeam;
};

