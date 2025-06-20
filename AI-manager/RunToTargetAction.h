#pragma once
#include "Agent.h"
#include "OldAction.h"
#include"Option.h"
#include <variant>
#include <any>



class RunToTargetAction :
	public OldAction
{
public:
	RunToTargetAction(Agent* target);
	void onActionStart(Agent *currentA) override;
	void onActionUpdate(Agent* currentA, float dt, AgentManager* am) override;
	void onActionFinished(Agent* currentA) override;
	bool isFinished() override;

	static std::unique_ptr<OldAction> create(Option* data) {

		return std::make_unique<RunToTargetAction>(data->getParameter<Agent*>("Target"));
	}
private:
	float savedSpeed = 0;
	float distance = std::numeric_limits<float>::max();
	int m_runSpeed = 20;
	Agent* m_target;
};

