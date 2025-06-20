#pragma once
#include "IComponent.h"
#include "Target.h"
#include "Agent.h"
class TargetSet:public IComponent
{
public:
	TargetSet(Agent* targetAgent);
	void render(Agent* a, sf::RenderTarget& rt) const override;
	void update(Agent*a, float deltaTime, AgentManager*) override;
private:
	Agent* m_currentTarget;
};

