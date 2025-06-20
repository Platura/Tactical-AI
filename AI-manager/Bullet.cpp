#include "Bullet.h"
#include "Agent.h"
#include "MathHelpers.h"
#include <iostream>

#include "MapDebugDisplay.h"
#include "imgui.h"
#include "fmt/format.h"

Bullet::Bullet(sf::Vector2f start, sf::Vector2f end):m_position(start), m_target(end)
{
	if (!m_texture.loadFromFile(R"(textures\bullet.png)")) {
		// Handle error if the texture doesnt load
		std::cout << "Error loading texture!" << std::endl;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
}

void Bullet::render(Agent* a, sf::RenderTarget& rt) const
{
	rt.draw(m_sprite);
}

void Bullet::update(Agent* a, float deltaTime, AgentManager* am)
{
	sf::Vector2f direction = m_target - m_position;
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);

	if (length > 0)
	{
		direction /= length;
		m_position += direction * m_bullet_speed*deltaTime;
		float angle = std::atan2(direction.y, direction.x) * 180 / 3.14f;
		m_sprite.setRotation(angle -90);
	}
	if (length < m_bullet_speed*deltaTime)
	{
		m_position = m_target;

		a->removeComponent<Bullet>();
	}

	m_sprite.setPosition(m_position);
}

void Bullet::drawDebug()
{
}
