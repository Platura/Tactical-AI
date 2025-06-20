#pragma once
#include "Types.hpp"
#include "Costfield.h"
class IEngineDataOutput
{
public:
	virtual void setup(aiAgentId) = 0;

	virtual void moveTo(aiAgentId, Vec2D pos) = 0;
	virtual void moveTo(aiAgentId, Vec2D pos, Costfield cost) = 0;
	virtual void shootAt(aiAgentId, Vec2D pos) = 0;
	virtual void dealDamage(aiAgentId, int dmg) = 0;
	virtual void setCover(aiAgentId, float cover_value) = 0;
	virtual void meleeAt(aiAgentId, Vec2D pos) = 0;
	virtual void reload(aiAgentId) = 0;
	virtual void rotate(aiAgentId, float rot) = 0;
	virtual bool isActionRunning(aiAgentId) = 0;
	virtual void stopAction(aiAgentId a) = 0;
};

