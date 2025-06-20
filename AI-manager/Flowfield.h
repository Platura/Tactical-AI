#pragma once
#include "Field.h"
#include <SFML/Graphics.hpp>
#include <vector>
class Flowfield
{
public:
	Flowfield();
	//init() Feld mit Größe der ganzen Karte
	void init(Field<int> const& tilemap, Field<uint32_t> const& costmap, sf::Vector2f const& tile_size);
	void integrate(std::vector<sf::Vector2i> const& targets);
	void computeDirection();
	Field<sf::Vector2f> const& getData() const {
		return m_flowField;
	}
	Field<float> const& getIntegrationData() const {
		return m_integrationField;
	}

	sf::Vector2f getAtWorldPos(sf::Vector2f pos) const;
	sf::Vector2i worldToGridPos(sf::Vector2f world_pos) const;

	bool isPosAtTarget(sf::Vector2f from) const;
private:
	void resetIntegration();
	Field<sf::Vector2f> m_flowField;

	Field<float> m_integrationField;
	Field<uint32_t> m_costField;
	std::vector<std::pair<uint32_t, uint32_t>> m_savedTargets;
	sf::Vector2f m_tile_size;
};

