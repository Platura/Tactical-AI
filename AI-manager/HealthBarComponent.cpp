#include "HealthBarComponent.h"
#include "Agent.h"

void HealthBarComponent::update(Agent*a, float deltaTime, AgentManager*)
{
	m_hp.setPosition(a->getPosition());
	auto h = a->getHealth();

	if (h != m_last_hp_value)
	{
		m_last_hp_value = h;
		m_hp.setState(float(h) / a->getMaxHealth());
	}
}

void HealthBarComponent::render(Agent*, sf::RenderTarget&rt) const
{
	rt.draw(m_hp);
}
