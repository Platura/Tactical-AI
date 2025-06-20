#include "GraphicComponent.h"
#include <iostream>
#include "Agent.h"
GraphicComponent::GraphicComponent(std::string image_path)
{
	loadCharacter(image_path);
}

void GraphicComponent::loadCharacter(std::string path)
{
	if (!m_texture.loadFromFile(path)) {
		std::cout << "Error occured when trying to load the character texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	auto const& size = m_texture.getSize();
	m_sprite.setOrigin( size.x * 0.5,size.y * 0.5);

	//m_sprite.setScale({ 0.12,0.12 });
}

void GraphicComponent::updatePosition(sf::Vector2f position)
{
	
}

void GraphicComponent::updateSprite(sf::Image image)
{
	m_texture.update(image);
}

void GraphicComponent::update(Agent* a, float deltaTime, AgentManager*)
{
	auto pos = a->getPosition();
	auto rot = a->getRotation();
	m_sprite.setPosition(pos);
	m_sprite.setRotation(rot);
}

void GraphicComponent::render(Agent* a, sf::RenderTarget& rt) const
{
	//sf::CircleShape circle(10.f);
	//circle.setOrigin(10.f, 10.f);
	//circle.setPosition(m_sprite.getPosition());
	//circle.setFillColor(sf::Color::Black);
	
	rt.draw(m_sprite);
	//rt.draw(circle);
}
