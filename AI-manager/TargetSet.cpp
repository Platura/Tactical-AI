#include "TargetSet.h"

TargetSet::TargetSet(Agent* targetAgent):m_currentTarget(targetAgent)
{
}

void TargetSet::render(Agent* a, sf::RenderTarget& rt) const
{
}

void TargetSet::update(Agent* a, float deltaTime, AgentManager*)
{
	auto const pos = a->getPosition();
	auto move = m_currentTarget->getComponent<Target>()->getFlowfield().getAtWorldPos(pos) * deltaTime * a->getSpeed();
	a->setPosition(pos + move);
}
