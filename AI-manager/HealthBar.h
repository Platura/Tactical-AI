#pragma once
#include <SFML/Graphics.hpp>

class HealthBar : public sf::Drawable, public sf::Transformable
{
	sf::Vector2f m_offset = sf::Vector2f(0.f, -20.f);
	float m_width = 50;
	float m_height = 6;
	float m_state = 0.7f;

	sf::RectangleShape m_background;
	sf::RectangleShape m_foreground;
	sf::RectangleShape m_forground_highlight;

public:
	HealthBar();

	void setState(float state)
	{
		m_state = state;
		updateState();
	}

	void updateState();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

