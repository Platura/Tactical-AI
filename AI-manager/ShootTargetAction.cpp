#include "ShootTargetAction.h"
#include "Agent.h"
#include "Bullet.h"
#include "MathHelpers.h"

ShootTargetAction::ShootTargetAction(Agent* target) : m_target(target)
{
}

void ShootTargetAction::onActionStart(Agent* currentA)
{
	//savedSpeed = currentA->getSpeed();
	//currentA->setSpeed(m_standSpeed);
	currentAmmunition = currentA->getAmmunition();
	
}

void ShootTargetAction::onActionUpdate(Agent* currentA, float dt, AgentManager* am)
{
	
}

void ShootTargetAction::onActionFinished(Agent* currentA)
{
	currentA->setAmmunition(currentAmmunition);
}

bool ShootTargetAction::isFinished()
{
	//Schießen bis Gegner tot, in Deckung oder Munition alle
	return currentAmmunition<10;
}
