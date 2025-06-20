#pragma once
#include <SFML/Graphics.hpp>
#include "IComponent.h"
#include "Flowfield.h"
class MovementComponent :
	public IComponent
{
public:
	MovementComponent(Flowfield flowField);
	~MovementComponent();
	void calculateMovement(Agent* a);
	void init() override;
	void render(Agent* a, sf::RenderTarget& rt) const override;
	void update(Agent*, float deltaTime, AgentManager*) override;

	bool hasReachedTarget() const
	{
		return at_target;
	}
private:
	Flowfield m_field;
	const float m_speed = 10;
	bool at_target = false;
};

