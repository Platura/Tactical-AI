#pragma once
#include "Agent.h"
class OldAction
{
public:

	virtual ~OldAction() = default;

	virtual void onActionStart(Agent *currentA) = 0;
	virtual void onActionUpdate(Agent* currentA, float dt, AgentManager* am) = 0;
	virtual void onActionFinished(Agent* currentA) = 0;

	virtual bool isFinished() = 0;
};

