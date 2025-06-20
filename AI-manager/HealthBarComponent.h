#pragma once
#include "IComponent.h"
#include "HealthBar.h"

class HealthBarComponent :
    public IComponent
{
    HealthBar m_hp;
    int m_last_hp_value = 0.f;
public:
    void update(Agent*, float deltaTime, AgentManager*) override;
    void render(Agent*, sf::RenderTarget&) const override;
};

