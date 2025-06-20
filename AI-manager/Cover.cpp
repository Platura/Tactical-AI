#include "Cover.h"
#include "Agent.h"

Cover::Cover(sf::Vector2f const& tile_size):m_tile_size(tile_size)
{
}

void Cover::render(Agent* a, sf::RenderTarget& rt) const
{
}

void Cover::update(Agent*a, float deltaTime, AgentManager* am)
{
	m_agent = a;
}
CoverInfo Cover::getBestCover(Agent* enemy) {
	auto best_cover_pos = m_agent->getPosition() + enemy->getHeading() + m_tile_size;
	return CoverInfo{ .cover_pos = best_cover_pos, .cover_value = 0.9 };
};

void Cover::drawDebug()
{
}
