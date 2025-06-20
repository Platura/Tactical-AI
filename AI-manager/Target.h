#pragma once
#include "IComponent.h"
#include "Flowfield.h"
#include "MapManager.h"
class Target :
	public IComponent
{

public:
	Target(MapManager& map);
	~Target();
	void render(Agent* a, sf::RenderTarget& rt) const override;
	void update(Agent*a, float deltaTime, AgentManager*) override;
	void drawDebug();
	//update(
		//flowfield berechnen wenn nicht vorhanden
		//letzte pos speichern agent
		//flowfield neu berechnen->ab bestimmter distanz
	//)
	Flowfield& getFlowfield();
private:
	Flowfield m_flowfield;
	MapManager &m_map;
	sf::Vector2f m_savedFlowfieldPosition;
};

