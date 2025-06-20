#pragma once
#include <SFML/Graphics.hpp>
class Camera
{
private:
	sf::Vector2f m_origin;
	sf::Vector2f m_screenSize;
	sf::Vector2i m_lastMousePos;
	bool m_lastMousePosSet = false;
	float m_scale = 1.0f;
public:
	Camera() = default;
	Camera(sf::View const& view);
	sf::View getView() const;
	sf::Vector2f screenToWorld(sf::Vector2f const& in) const;
	void onEvent(sf::Event const& ev);
};

