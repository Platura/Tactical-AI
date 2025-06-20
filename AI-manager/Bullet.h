#pragma once
#include "IComponent.h"
#include <SFML/Graphics.hpp>

class Bullet :
	public IComponent
{
public:
	Bullet(sf::Vector2f start, sf::Vector2f end);
	void render(Agent* a, sf::RenderTarget& rt) const override;
	void update(Agent*, float deltaTime, AgentManager* am) override;
	void drawDebug();
private:
	float m_bullet_speed = 300;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	sf::Vector2f m_target;
};

