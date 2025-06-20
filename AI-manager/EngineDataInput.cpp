#include "EngineDataInput.h"

Costfield& EngineDataInput::getCostField() const
{
    return cmap;
}

void* EngineDataInput::getNativeAgentHandle(aiAgentId id)
{
    return (void*)getAgent(id);
}

Vec2D EngineDataInput::getAgentPosition(aiAgentId id) const
{
    auto pos = getAgent(id)->getPosition();
    return { pos.x, pos.y };
}

Vec2D EngineDataInput::getAgentDirection(aiAgentId id) const
{
    auto direction = getAgent(id)->getHeading();
    return { direction.x, direction.y };
}

float EngineDataInput::getAgentRotation(aiAgentId id) const
{
    auto rot = getAgent(id)->getRotation();
    return rot;
}

int EngineDataInput::getAgentStance(aiAgentId id) const
{
    auto stance = getAgent(id)->getStance();
    return (stance);
}

int EngineDataInput::getAgentAmmunition(aiAgentId id) const
{
    auto ammunition = getAgent(id)->getAmmunition();
    return ammunition;
}

int EngineDataInput::getAgentHealth(aiAgentId id) const
{
    auto health = getAgent(id)->getHealth();
    return health;
}

float EngineDataInput::getDeltaTime(aiAgentId id) const
{
    return getAgent(id)->getDeltaTime();
}

DataInputMapSize EngineDataInput::getMapSize() const
{
    return m_map_size;
}

Agent* EngineDataInput::getAgent(aiAgentId id) const
{
    return m_agm->getAgent(id);
}
