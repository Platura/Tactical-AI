#pragma once
#include "TacticalMap.h"
#include "Costfield.h"
#include "Types.hpp"
#include <SFML/Graphics.hpp>
class MovementMap
{
	//Map that displays the costs of movement
public:
	MovementMap() = default;
	TacticalMap compute(aiPosition pos, Costfield cmap);
private:
	std::vector<std::pair<uint32_t, uint32_t>> m_savedTargets;

	TacticalMap m_flowField;

	TacticalMap tm;
};

