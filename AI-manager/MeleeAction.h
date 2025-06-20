#pragma once
#include "OldAction.h"
#include "TileMap.h"
#include "Option.h"
class MeleeAction :
	public OldAction
{
public:
	MeleeAction(Agent* enemy);
	void onActionStart(Agent* currentA) override;
	void onActionUpdate(Agent* currentA, float dt, AgentManager* am) override;
	void onActionFinished(Agent* currentA) override;
	bool isFinished() override;

	static std::unique_ptr<OldAction> create(Option* data) {

		return std::make_unique<MeleeAction>(data->getParameter<Agent*>("Target"));
	}
private:
	float m_meleeRange = 20.f;
	float m_meleeDamage = 50.f;
	Agent* m_enemy;
};

