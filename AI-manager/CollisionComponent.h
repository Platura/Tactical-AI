#pragma once
#include "IComponent.h"
class CollisionComponent :
	public IComponent
{
public:
	CollisionComponent();
	void render(Agent* a, sf::RenderTarget& rt) const override;
	void update(Agent*, float deltaTime, AgentManager* ) override;
private:
};

