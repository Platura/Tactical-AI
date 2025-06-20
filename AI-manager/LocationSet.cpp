#include "LocationSet.h"
#include "MathHelpers.h"
#include "MapManager.h"

LocationSet::LocationSet(sf::Vector2f location) :m_setLocation(location)
{
}

inline void LocationSet::onAssign(Agent* a) 
{
	IComponent::onAssign(a);
	// flow field berechnen
	m_flowfield = (*MapManager::getInstance()).computeFlowfield({ m_setLocation });
}

void LocationSet::render(Agent* a, sf::RenderTarget& rt) const
{
}

void LocationSet::update(Agent* a, float deltaTime, AgentManager*)
{
	auto const pos = a->getPosition();
	auto move = m_flowfield.getAtWorldPos(pos) * deltaTime * a->getSpeed();
	a->setPosition(pos + move);
}