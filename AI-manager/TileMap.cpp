#include "TileMap.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

TileMap::TileMap()
{
}

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height)
{
	//return false if the tileset doesnt load
	if (!m_tileset.loadFromFile(tileset))
		return false;
	const int vertexNumber = 6;
	m_vertices.setPrimitiveType(sf::Triangles);
	m_vertices.resize(width * height * vertexNumber);
	for (unsigned int x = 0; x < width; ++x) 
	{
		for (unsigned int y = 0; y < height; ++y)
		{
			//current tile index
			int tileIndex = m_map_data.at(x, y);
			//uv coords from the tilemap
			auto const tileset_size_x = 16;
			auto const tileset_size_y = 16;


			int tu = tileIndex % (m_tileset.getSize().x / tileset_size_x) ;
			int tv = tileIndex / (m_tileset.getSize().x / tileset_size_x) ;
			
			//pointer array for the vertices of the two triangles of one tile
			sf::Vertex* triangles = &m_vertices[(x + y * width) * vertexNumber];

			triangles[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
			triangles[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
			triangles[2].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);
			triangles[3].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);
			triangles[4].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
			triangles[5].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);

			triangles[0].texCoords = sf::Vector2f(tu * tileset_size_x, tv * tileset_size_y);
			triangles[1].texCoords = sf::Vector2f((tu + 1) * tileset_size_x, tv * tileset_size_y);
			triangles[2].texCoords = sf::Vector2f(tu * tileset_size_x, (tv + 1) * tileset_size_y);
			triangles[3].texCoords = sf::Vector2f(tu * tileset_size_x, (tv + 1) * tileset_size_y);
			triangles[4].texCoords = sf::Vector2f((tu + 1) * tileset_size_x, tv * tileset_size_y);
			triangles[5].texCoords = sf::Vector2f((tu + 1) * tileset_size_x, (tv + 1) * tileset_size_y);
		}
	}
	return true;
}

bool TileMap::read_map_from_file(std::string path)
{
	//reads txt file from path
	std::fstream file(path,std::ios::in);

	std::string tileset_path;
	//take the first line which is the texture path
	std::getline(file, tileset_path);
	//take the second line which is the tileamount with width and height
	std::string tileMapSize;
	std::getline(file, tileMapSize);

	auto size = split(tileMapSize);

	int width = size[0];
	int height = size[1];
	m_mapSize = sf::Vector2i{ width, height };

	m_map_data.init(width, height);

	//take the rest which defines the tiles that should be set
	int y = 0;
	while (!file.eof())
	{
		std::string line;
		std::getline(file, line);
		auto line_data = split(line);

		for (int x = 0; x < width; ++x)
		{
			m_map_data.at(x, y) = line_data[x];
		}
		y++;
	}

	fs::path tpath(path);
	tpath.replace_filename(tileset_path);
	return load(tpath.string(), m_tileSize, width, height);
}


bool TileMap::write_map_to_file(std::string path)
{
	return true;
}

std::vector<int> TileMap::split(std::string inputString)
{
	std::stringstream partString(inputString);
	std::vector<int> output;
	while (!partString.eof())
	{
		std::string element;
		std::getline(partString, element, ',');

		output.push_back(std::atoi(element.c_str()));
	}
	return output;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &m_tileset;
	target.draw(m_vertices, states);
}
