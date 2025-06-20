#pragma once
#include "IEngineDataOutput.h"
#include "AgentManager.h"
#include "AiMemoryComponent.h"
#include "Costfield.h"

class EngineDataOutput:public IEngineDataOutput
{
	AgentManager* m_agm;
public:
	EngineDataOutput(AgentManager* am) :m_agm(am) {};
	void setup(aiAgentId) override;
	void moveTo(aiAgentId, Vec2D pos)override;
	void moveTo(aiAgentId, Vec2D pos, Costfield cost)override;
	void shootAt(aiAgentId, Vec2D pos)override;
	void dealDamage(aiAgentId, int dmg)override;
	void setCover(aiAgentId, float cover_value)override;
	void meleeAt(aiAgentId, Vec2D pos)override;
	void reload(aiAgentId)override;
	void rotate(aiAgentId, float rot)override;
	bool isActionRunning(aiAgentId)override;
	void stopAction(aiAgentId a)override;
protected:
	Agent* getAgent(aiAgentId id) const;
	void switchAction(Agent* a, status new_Action) const;
};

