#include "MovementComponent.h"
#include "Agent.h"
#include "MapDebugDisplay.h"
#include "imgui.h"
#include <fmt/format.h>

MovementComponent::MovementComponent(Flowfield flowField)
{
	m_field = flowField;

}

MovementComponent::~MovementComponent()
{
	MapDebugDisplay::getInstance()->remove(&m_field);
}

void MovementComponent::calculateMovement(Agent* a)
{

}

void MovementComponent::init()
{
	MapDebugDisplay::getInstance()->register_map(&m_field, fmt::format("Flowfield Agent {}", m_agent->getId()));

}

void MovementComponent::render(Agent* a, sf::RenderTarget& rt) const
{
}



void MovementComponent::update(Agent* a, float deltaTime, AgentManager*)
{
	auto const pos = a->getPosition();
	auto move = m_field.getAtWorldPos(pos) * deltaTime * m_speed;
	ImGui::Begin("Test");
	ImGui::Value("Pos x", pos.x);
	ImGui::Value("Pos y", pos.y);

	ImGui::End();

	auto const new_pos = pos + move;
	a->setPosition(new_pos);

	//at_target = m_field.isPosAtTarget(new_pos);
	at_target = move == sf::Vector2f{ 0,0 };
}
