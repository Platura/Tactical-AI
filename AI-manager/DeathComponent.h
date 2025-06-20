#pragma once
#include "IComponent.h"
class DeathComponent :
    public IComponent
{
public:
    DeathComponent();
    void render(Agent* a, sf::RenderTarget& rt) const override;
    void update(Agent*, float deltaTime, AgentManager*) override;
private:

};

