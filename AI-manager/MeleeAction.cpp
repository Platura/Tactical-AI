#include "MeleeAction.h"
#include "MathHelpers.h"
#include "TargetSet.h"
#include <iostream>

MeleeAction::MeleeAction(Agent* enemy):m_enemy(enemy)
{
}

void MeleeAction::onActionStart(Agent* currentA)
{

}

void MeleeAction::onActionUpdate(Agent* currentA, float dt, AgentManager* am)
{
	if (getDistance(currentA->getPosition(), m_enemy->getPosition()) <= m_meleeRange)
	{
		currentA->removeComponent<TargetSet>();
		m_enemy->setDamage(m_meleeDamage);
	}
	else {
		auto const pos = currentA->getPosition();
		auto move = getDirection(pos,m_enemy->getPosition()) * dt * currentA->getSpeed();
		currentA->setPosition(pos + move);
	}
}

void MeleeAction::onActionFinished(Agent* currentA)
{
	
}

bool MeleeAction::isFinished()
{
	return m_enemy->getHealth()<=0;
}
