#pragma once
#include "IComponent.h"
#include <SFML/Graphics.hpp>
class NameTagComponent :
    public IComponent
{
    sf::Font m_font;
    sf::Text m_name;
    sf::Vector2f m_offset = { 0, -50 };
public:
    void init() override;

    void update(Agent*, float deltaTime, AgentManager*) override;
    void render(Agent*, sf::RenderTarget&) const override;
};

