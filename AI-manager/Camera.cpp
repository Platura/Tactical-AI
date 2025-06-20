#include "Camera.h"

Camera::Camera(sf::View const& view) 
	: m_origin(view.getCenter())
	, m_screenSize(view.getSize())
{
}

sf::View Camera::getView() const
{
	return sf::View{ m_origin, m_screenSize * m_scale };
}

sf::Vector2f Camera::screenToWorld(sf::Vector2f const& in) const
{
	sf::Vector2f out = (in - m_screenSize * 0.5f) * m_scale + m_origin;
	return out;
}

void Camera::onEvent(sf::Event const& ev)
{
	switch (ev.type)
	{
	case sf::Event::Resized:
	{
		m_screenSize = sf::Vector2f{ (float)ev.size.width, (float)ev.size.height };
		break;
	}
	case sf::Event::MouseButtonPressed:
	{
		auto const& [button, xCoord, yCoord] = ev.mouseButton;
		if (button == sf::Mouse::Button::Left)
		{
			m_lastMousePos = { xCoord,yCoord };
			m_lastMousePosSet = true;
		}
		break;
	}
	case sf::Event::MouseButtonReleased:
		if (ev.mouseButton.button == sf::Mouse::Button::Left)
		{
			m_lastMousePosSet = false;
		}
		break;
	case sf::Event::MouseMoved:
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_lastMousePosSet)
		{
			sf::Vector2i currentMousePos{ ev.mouseMove.x,ev.mouseMove.y };
			auto delta = currentMousePos - m_lastMousePos;
			m_lastMousePos = currentMousePos;
			m_origin -= sf::Vector2f{ (float)delta.x,(float)delta.y }*m_scale;
		}
		break;
	case sf::Event::MouseWheelScrolled:
		m_scale -= ev.mouseWheelScroll.delta * 0.2f;
		m_scale = std::clamp(m_scale, 0.2f, 4.f);
		break;
	case sf::Event::KeyPressed:
		break;
	default:
		break;
	}
}
