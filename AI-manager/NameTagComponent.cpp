#include "NameTagComponent.h"
#include "Agent.h"
#include <fmt/format.h>
void NameTagComponent::init()
{
	m_font.loadFromFile("./Fonts/Roboto-Black.ttf");
	m_name.setFont(m_font);
	m_name.setCharacterSize(20);

	auto str = fmt::format("{}", m_agent->getId());
	m_name.setString(str);
	m_name.setOrigin((m_name.getCharacterSize() * str.size()) / 2, 0);
	m_name.setPosition(m_offset);
}

void NameTagComponent::update(Agent*, float deltaTime, AgentManager*)
{

}

void NameTagComponent::render(Agent*, sf::RenderTarget& rt) const
{
	auto state = sf::RenderStates::Default;
	state.transform.translate(m_agent->getPosition());

	rt.draw(m_name, state);
}
