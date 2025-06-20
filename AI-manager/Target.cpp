#include "Target.h"
#include "Agent.h"
#include "imgui.h"
#include "SFML/Graphics.hpp"

#include "MapDebugDisplay.h"

Target::Target(MapManager& map):m_map(map)
{
	MapDebugDisplay::getInstance()->register_map(&m_flowfield, "name");
}

Target::~Target()
{
	MapDebugDisplay::getInstance()->remove(&m_flowfield);
}

void Target::render(Agent* a, sf::RenderTarget& rt) const
{
}

void Target::update(Agent*a, float deltaTime, AgentManager*)
{
	
	auto currentPos=a->getPosition();
	//return wenn Target position sich nicht geändert hat
	if (m_savedFlowfieldPosition == currentPos)
	{
		return;
	}
	auto const distance = currentPos - m_savedFlowfieldPosition;
	auto length = distance.x * distance.x + distance.y * distance.y;
	//distance ist größer als vertretbar also neu berechenen
	if (length > 20 * 20) {
		//recalculate flowfield
		m_flowfield = m_map.computeFlowfield({ currentPos });
	}

}

void Target::drawDebug()
{
	auto debug_display = MapDebugDisplay::getInstance();
	bool check = &m_flowfield == debug_display->getCurrentMap();
	if (ImGui::Checkbox("FlowField", &check))
	{
		if (check)
		{
			debug_display->setCurrentMap(&m_flowfield);
		}
		else
		{
			debug_display->setCurrentMap("nullptr");
		}
	}
}

Flowfield& Target::getFlowfield()
{
	return m_flowfield;
}
