#include "DeathComponent.h"
#include "Agent.h"

DeathComponent::DeathComponent()
{
}

void DeathComponent::render(Agent* a, sf::RenderTarget& rt) const
{
}

void DeathComponent::update(Agent* a, float deltaTime, AgentManager* am)
{
	auto currentHealth = a->getHealth();
	if (currentHealth <= 0)
	{
		am->removeAgent(a);
	}
}
