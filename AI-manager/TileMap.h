#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Field.h"


class TileMap:public sf::Drawable, public sf::Transformable
{
	const std::string c_tile_map_name;
public:
	TileMap();
	bool load(const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height);

	bool read_map_from_file(std::string path);
	bool write_map_to_file(std::string path);
	static std::vector<int> split(std::string inputString);
	sf::Vector2u getTileSize() { return m_tileSize; };
	sf::Vector2i getMapSize() { return m_mapSize; };

	Field<int>& get_map_data() { return m_map_data; }
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	sf::Vector2u m_tileSize = { 32, 32 };
	sf::Vector2i m_mapSize;
	Field<int> m_map_data;
};

