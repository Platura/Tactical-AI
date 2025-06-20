#include "ReasonerComponent.h"
#include "MapDebugDisplay.h"

#include "Global.h"

ReasonerComponent::ReasonerComponent(std::vector<Option> decisions)
{
	for (auto& el : decisions)
	{
		//m_reasoner->addOption(std::move(std::make_shared<Option>(el)));
	}
}

void ReasonerComponent::render(Agent* a, sf::RenderTarget& rt) const
{
}

void ReasonerComponent::update(Agent* a, float deltaTime, AgentManager*)
{
	/*
	auto actions = m_reasoner->update();

	auto action_to_run = actions[0];

	if (m_current_action != action_to_run->getName())
	{
		m_current_action = action_to_run->getName();
		auto i_action = actionMapper.at(m_current_action)(action_to_run);

		a->getComponent<ActionRunner>()->setAction(std::move(i_action));
	}
	*/
}

void ReasonerComponent::drawDebug()
{
	//m_reasoner->DrawDebugUi();
}
