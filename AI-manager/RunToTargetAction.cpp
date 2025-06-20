#include "RunToTargetAction.h"
#include "LocationSet.h"
#include "TargetSet.h"
#include "MathHelpers.h"

RunToTargetAction::RunToTargetAction(Agent* target) : m_target(target)
{
}

void RunToTargetAction::onActionStart(Agent *currentA)
{
	savedSpeed=currentA->getSpeed();
	currentA->setSpeed(m_runSpeed);

	currentA->addComponent<TargetSet>(m_target);

	/*std::visit([currentA](auto&& e) {
		using T = std::decay_t<decltype(e)>;
		if constexpr (std::is_same_v<T, sf::Vector2f>)
		{
			currentA->addComponent<LocationSet>(e);
		}
		else if constexpr (std::is_same_v<T, Agent*>)
		{
			currentA->addComponent<TargetSet>(e);
		}
		}, m_target);*/
	
}

void RunToTargetAction::onActionUpdate(Agent* currentA, float dt, AgentManager* am)
{
	/*auto pos = std::visit([](auto&& e) {
		using T = std::decay_t<decltype(e)>;
			if constexpr (std::is_same_v<T, sf::Vector2f>)
			{
				return e;
			}
			else if constexpr (std::is_same_v<T, Agent*>)
			{
				return e->getPosition();
			}
		}, m_target);*/

	distance = getLength(currentA->getPosition() - m_target->getPosition());
}

void RunToTargetAction::onActionFinished(Agent* currentA)
{
	currentA->setSpeed(savedSpeed);
	currentA->removeComponent<TargetSet>();
}

bool RunToTargetAction::isFinished()
{
	return distance < 25.f;
}
