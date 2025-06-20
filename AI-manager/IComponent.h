#pragma once
#include <SFML/Graphics.hpp>
class Agent;
class AgentManager;

class IComponent
{
protected:
	Agent* m_agent;
public:
	virtual ~IComponent() {};

	virtual void onAssign(Agent* a) { m_agent = a; }

	// Is called after assign
	virtual void init() {}

	virtual void update(Agent*, float deltaTime, AgentManager*) = 0;
	virtual void render(Agent*, sf::RenderTarget&) const = 0;
	virtual void drawDebug() {};

};

