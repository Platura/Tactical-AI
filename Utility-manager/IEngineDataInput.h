#pragma once
#include "Types.hpp"
#include "Costfield.h"

struct DataInputMapSize
{
	uint32_t tiles_x;
	uint32_t tiles_y;
	uint32_t tile_size_X;
	uint32_t tile_size_y;

};

class IEngineDataInput
{
public:

	virtual Costfield &getCostField() const = 0;
	virtual void* getNativeAgentHandle(aiAgentId) = 0;
	virtual Vec2D getAgentPosition(aiAgentId) const = 0;
	virtual Vec2D getAgentDirection(aiAgentId) const = 0;
	virtual float getAgentRotation(aiAgentId) const = 0;
	virtual int getAgentStance(aiAgentId)const = 0;
	virtual int getAgentAmmunition(aiAgentId)const = 0;
	virtual int getAgentHealth(aiAgentId)const = 0;
	virtual float getDeltaTime(aiAgentId)const = 0;
	virtual DataInputMapSize getMapSize() const = 0;

};

