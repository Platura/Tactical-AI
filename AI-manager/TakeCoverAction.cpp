#include "TakeCoverAction.h"
#include "Cover.h"
#include "LocationSet.h"
#include "MathHelpers.h"

TakeCoverAction::TakeCoverAction(Agent* cover,Agent* enemy):m_enemy(enemy),m_cover(cover)
{
}

void TakeCoverAction::onActionStart(Agent* currentA)
{
	m_cover_pos = m_cover->getComponent<Cover>()->getBestCover(m_enemy).cover_pos;
	m_cover_value = m_cover->getComponent<Cover>()->getBestCover(m_enemy).cover_value;
	currentA->setCoverValue(m_cover_value);

	currentA->addComponent<LocationSet>(m_cover_pos);
}

void TakeCoverAction::onActionUpdate(Agent* currentA, float dt, AgentManager* am)
{
	stayInCover += dt;
	distance = getLength(currentA->getPosition() - m_cover_pos);
}

void TakeCoverAction::onActionFinished(Agent* currentA)
{
	currentA->setCoverValue(0);
	currentA->removeComponent<LocationSet>();
	stayInCover = 0;
}

bool TakeCoverAction::isFinished()
{
	return (stayInCover==1000|| distance < 25.f);
}
