#pragma once
#include "IComponent.h"

struct CoverInfo {
	sf::Vector2f cover_pos;
	float cover_value;
};

class Cover :
    public IComponent
{
public:
	//add Covermap
	Cover(sf::Vector2f const& tile_size);
	void render(Agent* a, sf::RenderTarget& rt) const override;
	void update(Agent*a, float deltaTime, AgentManager* am) override;
	void drawDebug();
	CoverInfo getBestCover(Agent* enemy);
private:
	Agent* m_agent;
	sf::Vector2f m_tile_size;
};