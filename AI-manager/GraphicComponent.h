#pragma once
#include <SFML/Graphics.hpp>
#include "IComponent.h"
class GraphicComponent : public IComponent
{
public:
	GraphicComponent(std::string image_path);
	~GraphicComponent() = default;

	void loadCharacter(std::string path);
	void updatePosition(sf::Vector2f position);
	void updateSprite(sf::Image image);
	

	void render(Agent* a, sf::RenderTarget& rt) const override;
	void update(Agent*, float deltaTime, AgentManager*) override;
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};


