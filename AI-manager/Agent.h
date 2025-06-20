#pragma once
#include "GraphicComponent.h"
#include "AgentManager.h"
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

class Agent
{
public:
	Agent();
	Agent(sf::Vector2f position);
	void setPosition(sf::Vector2f nPosition);
	void update(float deltaTime, AgentManager*am);
	void render(sf::RenderTarget& rt);

	void drawDebug();

	template<typename T, typename... Args>
	IComponent* addComponent(Args && ... args);

	template<typename T>
	bool hasComponent() const;

	template<typename T>
	T* getComponent() const;

	template<typename T>
	void removeComponent();

	sf::Vector2f const& getPosition() const { return m_position; }
	sf::Vector2f const& getHeading()const { return m_direction; }
	float getSpeed()const { return m_movementSpeed; }
	void setSpeed(float speed);

	int getAmmunition()const { return m_primaryAmmunition; }
	int getMaxAmmunition()const { return m_maxAmmunition; }
	void setAmmunition(int ammo);

	int getCoverValue()const { return m_coverValue; }
	void setCoverValue(float coverValue);

	int getStance()const { return m_stance; }
	void setStance(int stance);

	int getHealth()const { return m_currentHealth; }
	int getMaxHealth()const { return m_maxHealth; }

	float getDeltaTime()const { return m_deltaTime; }

	void setDamage(int damage);
	void setHealth(int health);


	void setName(std::string name);
	void setRotation(float rot);
	float getRotation();
	
	std::string const &getName()const { return m_name; };

	void setId(uint32_t id) {
		m_id = id;
	}
	uint32_t getId() const {
		return m_id;
	}
private:
	uint32_t m_id;
	std::string m_name;
	int m_maxHealth = 100;
	int m_currentHealth = 100;
	float m_movementSpeed = 10.0;
	int m_maxAmmunition = 100;
	int m_primaryAmmunition = 100;
	float m_coverValue = 0;
	int m_stance = 0;
	float m_rot = 0;
	float m_deltaTime = 0;

	sf::Vector2f m_position{ 10,10 };
	sf::Vector2f m_old_position{};
	sf::Vector2f last_position = { 0.f, 0.f };

	sf::Vector2f m_direction = {0.f,0.f};
	
	std::unordered_map<std::type_index, std::unique_ptr<IComponent>> m_components;

	bool m_isComponentsUpdating = false;
	std::vector<std::type_index> m_components_to_delete;
};


template<typename T, typename... Args>
IComponent* Agent::addComponent(Args && ... args)
{
	std::unique_ptr<IComponent> component = std::make_unique<T>(std::forward<Args>(args)...);
	auto raw_ptr = component.get();
	raw_ptr->onAssign(this);
	raw_ptr->init();
	m_components.insert_or_assign(typeid(T), std::move(component));
	return raw_ptr;
}

template<typename T>
bool Agent::hasComponent() const
{
	auto it = m_components.find(typeid(T));
	return it != m_components.end();
}

template<typename T>
T* Agent::getComponent() const
{
	auto it = m_components.find(typeid(T));
	if (it == m_components.end())
	{
		return nullptr;
	}
	return static_cast<T*>( it->second.get());
}

template<typename T>
void  Agent::removeComponent()
{
	if (m_isComponentsUpdating)
	{
		m_components_to_delete.push_back(typeid(T));
	}
	else
	{
		m_components.erase(typeid(T));
	}
}