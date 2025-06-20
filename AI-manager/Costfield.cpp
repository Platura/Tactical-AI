#include "Costfield.h"
#include <fmt/format.h>

Costfield::Costfield(Field<int> const&tilemap )
{
	init(tilemap);
}

Costfield::Costfield(Field<float> const& costfield)
{
	init(costfield);
}


void Costfield::init(Field<int> const& tilemap)
{
	std::vector<uint32_t> m_cost_mapping = { 0,5,5,5,5,5, // Gras,
		1,1,//Straße
		5,5,5,5,5,5,5,5,//Gras
		1,1,1,1,//Straße
		5,5,5,5,5,//Gras
		2,2,//Dreck
		1,1,1,//Straße
		5,//Gras
		1,1,1,1,1,//Straße
		250,//Deckung
		255,255,255,255,255,255,255,255, 255,255,255,255,255,255,255,255,255,255,255,//Wand
		200,200,200,200,200,200,200,200,200,//Baum
		50,50,50,50,50,50,50,50,50,//Wasser
		255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255//Wand, Ruine
	 };
	//costs for lone outpost tileset
	/*std::vector<uint32_t> m_cost_mapping = {1, // Gras,
		10, // Wasser
		250,//Baeume
		255 };*/
	m_costField.init(tilemap.getSizeX(), tilemap.getSizeY());
	for (int x = 0; x < tilemap.getSizeX(); ++x) {
		for (int y = 0; y < tilemap.getSizeY(); ++y) {
			m_costField.at(x, y) = m_cost_mapping[tilemap.at(x, y)] ;
		}
	}
}

void Costfield::init(Field<float> const& tac)
{
	m_costField.init(tac.getSizeX(), tac.getSizeY(), 0);

	for (size_t i = 0; i < tac.getSize(); ++i)
	{
		float value = tac.getData()[i];
		m_costField.getData()[i] = uint32_t( std::max(0.f, std::min(255.f, value)));
	}
}
