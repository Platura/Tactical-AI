#pragma once
#include "IComponent.h"
#include "Agent.h"
#include "FlowField.h"
class LocationSet :public IComponent
{
public:
	LocationSet(sf::Vector2f location);
	void onAssign(Agent* a) override;

	void render(Agent* a, sf::RenderTarget& rt) const override;
	void update(Agent* a, float deltaTime, AgentManager*) override;
private:
	sf::Vector2f m_setLocation;
	Flowfield m_flowfield;
};