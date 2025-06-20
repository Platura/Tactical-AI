#pragma once
#include "IReasoner.h"
#include "IComponent.h"
class ReasonerComponent :
    public IComponent
{
public:
	ReasonerComponent() = default;
	ReasonerComponent(std::vector<Option> decisions);
	void render(Agent* a, sf::RenderTarget& rt) const override;
	void update(Agent*, float deltaTime, AgentManager*) override;
	void drawDebug();

	IReasoner& getReasoner()
	{
		return* m_reasoner;
	};

private:
	IReasoner* m_reasoner;
	std::string m_current_action;
};

