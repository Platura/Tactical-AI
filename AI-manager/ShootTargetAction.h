#pragma once
#include "OldAction.h"
#include "Option.h"
class ShootTargetAction :
	public OldAction
{
public:
	ShootTargetAction(Agent* target);
	void onActionStart(Agent* currentA) override;
	void onActionUpdate(Agent* currentA, float dt, AgentManager* am) override;
	void onActionFinished(Agent* currentA) override;
	bool isFinished() override;

	static std::unique_ptr<OldAction> create(Option* data) {

		return std::make_unique<ShootTargetAction>(data->getParameter<Agent*>("Target"));
	}
private:
	Agent* m_target;
	float savedSpeed = 0;
	float m_standSpeed = 0;
	int currentAmmunition = 0;
	int damage = 10;
	float lastShot = 0.f;

};

