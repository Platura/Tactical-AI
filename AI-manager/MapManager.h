#pragma once
#include "TileMap.h"
#include "Grid.h"
#include "Costfield.h"
#include "Flowfield.h"

class MapManager
{

	MapManager();
public:

	static MapManager* getInstance() {
		static MapManager instance;
		return &instance;
	}

	Flowfield computeFlowfield(const std::vector<sf::Vector2f>& targets);
	Flowfield computeFlowfield(const std::vector<sf::Vector2f>& targets, Costfield const& cost);

	void init(std::string path, const std::vector<sf::Vector2i>& targets);
	void draw(sf::RenderTarget& rt);
	Flowfield m_flow;

	auto& getTileMap() {
		return m_tilemap;
	}
	auto& getCostField() {
		return m_cost;
	}
private:
	Grid m_grid;
	TileMap m_tilemap;
	Costfield m_cost;
};

