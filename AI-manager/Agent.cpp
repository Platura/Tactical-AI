#include "Agent.h"
#include "imgui.h"
#include "MathHelpers.h"
#include <fmt/format.h>

Agent::Agent() : Agent({0,0})
{

}

Agent::Agent(sf::Vector2f position):  m_position(position)
{
	static int index = 0;
	m_name = fmt::format("Agent {}", index++);
	m_old_position = position;
}

void Agent::setPosition(sf::Vector2f nPosition)
{
	m_position = nPosition;
}

void Agent::update(float deltaTime, AgentManager *am)
{
	m_deltaTime = deltaTime;
	m_isComponentsUpdating = true;
	for (auto& [key, component] : m_components)
	{
		component->update(this, deltaTime, am);
	}
	m_isComponentsUpdating = false;

	if (!m_components_to_delete.empty())
	{
		for (auto el : m_components_to_delete) {
			m_components.erase(el);
		}
		m_components_to_delete.clear();
	}

	if (m_old_position != m_position)
	{
		m_direction = getDirection(m_old_position, m_position);
		m_old_position = m_position;
	}
	
	if (m_position != last_position)
	{
		m_direction = m_position - last_position;
		auto const rot = atan2(-m_direction.x, m_direction.y);
		m_rot = rot * 180 / 3.14;
		last_position = m_position;

	}
	
}

void Agent::render(sf::RenderTarget& rt)
{
	for (auto& [key, component] : m_components)
	{
		component->render(this, rt);
	}
}

void Agent::drawDebug()
{
	ImGui::Text(fmt::format("current Position {:.2f}x {:.2f}y", m_position.x, m_position.y).c_str());
	ImGui::Text(fmt::format("current Health {:} current, {:} maxHP", m_currentHealth, m_maxHealth).c_str());
	ImGui::Text(fmt::format("currentAmmunition {:} ammo, {:} maxAmmo", m_primaryAmmunition, 100).c_str());
	if (ImGui::TreeNode("Components"))
	{
		for (auto& [key, component] : m_components)
		{
			ImGui::CollapsingHeader(fmt::format("Components: {}", key.name()).c_str());
			component->drawDebug();
		}
		ImGui::TreePop();
	}
	ImGui::SliderFloat("Movement Speed", &m_movementSpeed, 0, 50);
}

void Agent::setSpeed(float speed)
{
	m_movementSpeed = speed;
}

void Agent::setAmmunition(int ammo)
{
	m_primaryAmmunition = ammo;
}

void Agent::setCoverValue(float coverValue)
{
	m_coverValue = coverValue;
}

void Agent::setStance(int stance)
{
	m_stance = stance;
}

void Agent::setDamage(int damage)
{
	float roll = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

	if (roll > m_coverValue)
	{
		m_currentHealth -= damage;
	}
}

void Agent::setHealth(int health)
{
	m_currentHealth += health;
}

void Agent::setName(std::string name)
{
	m_name = name;
}

void Agent::setRotation(float rot)
{
	m_rot = rot;
}

float Agent::getRotation()
{
	
	return m_rot;
}
