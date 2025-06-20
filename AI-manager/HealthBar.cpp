#include "HealthBar.h"

HealthBar::HealthBar()
{
	sf::Color background_c = sf::Color::Black;
	background_c.a = 255 * 0.3;
	m_background.setFillColor(background_c);
	m_foreground.setFillColor(sf::Color::Red);
	m_forground_highlight.setFillColor(sf::Color::White);
	updateState();
}

void HealthBar::updateState()
{
	

	m_background.setOrigin(m_width / 2, m_height / 2);
	m_background.setSize(sf::Vector2f(m_width, m_height));

	m_foreground.setPosition(-(m_width / 2), 0);
	m_foreground.setOrigin(0, m_height / 2);
	m_foreground.setSize(sf::Vector2f(m_width * m_state, m_height));

	m_forground_highlight.setPosition(-(m_width / 2) + 1, -(m_height / 2) + 1);
	m_forground_highlight.setOrigin(0, 0);
	m_forground_highlight.setSize(sf::Vector2f((m_width - 2) * m_state, (m_height / 2) - 1));


}

void HealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	states.transform *= getTransform();
	states.transform.translate(m_offset); 

	target.draw(m_background, states);
	target.draw(m_foreground, states);
	//target.draw(m_forground_highlight, states);
}
