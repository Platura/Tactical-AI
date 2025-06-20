#pragma once
#include <SFML/Graphics.hpp>
#include "Field.h"
#include <fmt/format.h>

class Grid : public sf::Drawable
{
public:
	Grid();
	Grid(int cellWidth, int cellHeight, int cellCountX, int cellCountY);
	void resize(int cellWidth, int cellHeight, int cellCountX, int cellCountY);
	template<typename T>
	void drawField(sf::RenderTarget& rt, Field<T> const& data);

	template<typename T>
	void drawValuesOnGrid(sf::RenderTarget& rt, Field<T> const& data);

	template<typename T>
	void drawColorOnGrid(sf::RenderTarget& rt, Field<T> const& data);

protected:
	virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const override;
private:
	sf::VertexArray m_grid;
	sf::Font m_roboto_font;
	sf::Vector2i m_cellWidth;
};

template<typename T>
void Grid::drawValuesOnGrid(sf::RenderTarget& rt, Field<T> const& data)
{
	auto const sx = data.getSizeX();
	auto const sy = data.getSizeY();
	sf::Text text;
	text.setFont(m_roboto_font);
	//text.setFillColor(sf::Color::Red);
	for (auto x = 0; x < sx; ++x)
	{
		for (auto y = 0; y < sy; ++y)
		{
			std::string value;
			if constexpr (std::is_same_v<float, T>)
			{
				float val = data.at(x, y);

				if (std::abs(val) < 0.01f)
					value = "";  // skip very small values
				else if (std::abs(val) > 9999.0f)
					value = "Åá";  // hide or symbol for large
				else
					value = fmt::format("{:.1f}", val);
			}
			else
				value = fmt::format("{}", data.at(x, y));
 
			text.setPosition(x*m_cellWidth.x, y*m_cellWidth.y);
			text.setString(value);
			text.setScale(0.5, 0.5);
			rt.draw(text);
		}
	}
	
}

template<typename T>
void Grid::drawColorOnGrid(sf::RenderTarget& rt, Field<T> const& data)
{
	auto const sx = data.getSizeX();
	auto const sy = data.getSizeY();
	sf::RectangleShape rect(sf::Vector2f{ (float)m_cellWidth.x, (float)m_cellWidth.y });
	auto color = sf::Color::Red;
	rect.setFillColor(color);

	for (auto x = 0; x < sx; ++x)
	{
		for (auto y = 0; y < sy; ++y)
		{
			color.a = 255 * data.at(x, y);
			rect.setFillColor(color);
			rect.setPosition(x * m_cellWidth.x, y * m_cellWidth.y);
			rt.draw(rect);
		}
	}
}

template<typename T>
void Grid::drawField(sf::RenderTarget& rt, Field<T> const& data)
{
	auto const sx = data.getSizeX();
	auto const sy = data.getSizeY();

	sf::RectangleShape line(sf::Vector2f(m_cellWidth.x/2, 1.f));

	sf::VertexArray lines(sf::PrimitiveType::Lines);
	for (auto x = 0; x < sx; ++x)
	{
		for (auto y = 0; y < sy; ++y)
		{
			const sf::Vector2f pos{ x * m_cellWidth.x + m_cellWidth.x / 2.f, y * m_cellWidth.y + m_cellWidth.x / 2.f };
			lines.append(pos);
			lines.append(pos + data.at(x, y) * float(m_cellWidth.x) * 0.5f);
		}


	}
	rt.draw(lines);
}

