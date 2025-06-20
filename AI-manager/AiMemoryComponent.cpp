#include "AiMemoryComponent.h"
#include "Agent.h"
#include "MovementComponent.h"


void AiMemoryComponent::render(Agent* a, sf::RenderTarget& rt) const
{
}

void AiMemoryComponent::update(Agent* a, float deltaTime, AgentManager*)
{
	if (is_finished)
		return;

	if (m_current_status == status::move)
	{
		if (a->getComponent<MovementComponent>()->hasReachedTarget())
		{
			is_finished = true;
		}
	}
}
