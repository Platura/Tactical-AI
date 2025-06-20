#pragma once
#include <iostream>
#include <vector>
#include "IReasoner.h"
#include "IEngineDataOutput.h"
#include "IEngineDataInput.h"
#include "Types.hpp"
class AgentBrain
{
private:
	aiAgentId id;
	IReasoner::ptr m_reasoner;
	size_t m_current_option = std::numeric_limits<size_t>::max();
	Option::ActionIt m_current_action;
	bool is_running_action = false;
public:

	AgentBrain() = default;
	AgentBrain(aiAgentId i, IReasoner::ptr ptr);

	aiAgentId getID() const { return id; }
	void reset();
	void update();

	void think(BlackboardManager& bm, IEngineDataOutput* cmd);
	void act(BlackboardManager& bm, IEngineDataOutput* cmd, IEngineDataInput* data);

	void DrawDebug();
private:

};

