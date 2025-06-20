#include "EngineDataOutput.h"

#include "AiMemoryComponent.h"
#include "MovementComponent.h"
#include "Bullet.h"
#include "MapManager.h"

void EngineDataOutput::setup(aiAgentId a)
{
	getAgent(a)->addComponent<AiMemoryComponent>();
}

void EngineDataOutput::moveTo(aiAgentId a, Vec2D pos)
{
	auto agent = getAgent(a);
	switchAction(agent, status::move);
	// Compute Flow Field
	//Some issues may arise as the flowfield gets calculated
	//May have to be reworked
	getAgent(a)->addComponent<MovementComponent>(MapManager::getInstance()->computeFlowfield({ {pos.x, pos.y} }));
}

void EngineDataOutput::moveTo(aiAgentId a, Vec2D pos, Costfield cost)
{
	auto agent = getAgent(a);
	switchAction(agent, status::move);
	// Compute Flow Field
	//Some issues may arise as the flowfield gets calculated
	//May have to be reworked
 	getAgent(a)->addComponent<MovementComponent>(MapManager::getInstance()->computeFlowfield({ {pos.x, pos.y} }, cost));
}

void EngineDataOutput::shootAt(aiAgentId id, Vec2D pos)
{
	auto start = getAgent(id)->getPosition();
	sf::Vector2f end = { pos.x,pos.y };
	getAgent(id)->addComponent<Bullet>(start, end);
}

void EngineDataOutput::dealDamage(aiAgentId id, int dmg)
{
	auto agent = getAgent(id);
	if (agent)
		getAgent(id)->setDamage(dmg);
	else
		fmt::print("Agent {} is already dead.\n", id);
}

void EngineDataOutput::setCover(aiAgentId id, float cover_value)
{
	auto agent = getAgent(id);
	if (agent)
		getAgent(id)->setCoverValue(cover_value);
}

void EngineDataOutput::meleeAt(aiAgentId, Vec2D pos)
{
}

void EngineDataOutput::reload(aiAgentId)
{
}

void EngineDataOutput::rotate(aiAgentId id, float rot)
{
	return getAgent(id)->setRotation(rot);
}

bool EngineDataOutput::isActionRunning(aiAgentId a)
{
	return getAgent(a)->getComponent<AiMemoryComponent>()->isActionRunning();
}

void EngineDataOutput::stopAction(aiAgentId a)
{
	auto a_ptr = getAgent(a);
	if (a_ptr->hasComponent< MovementComponent>())
	{
		a_ptr->removeComponent< MovementComponent>();
		a_ptr->getComponent<AiMemoryComponent>()->setCurrentStatus(status::idle);
	}
}

Agent* EngineDataOutput::getAgent(aiAgentId id) const
{
	return m_agm->getAgent(id);
}

void EngineDataOutput::switchAction(Agent* a, status new_Action) const
{

	auto mem = a->getComponent<AiMemoryComponent>();

	auto current_action = mem->getCurrentStatus();

	switch (current_action)
	{
	case status::move:
		a->removeComponent<MovementComponent>();
		break;
	default:
		break;
	}
	mem->setCurrentStatus(new_Action);
}
