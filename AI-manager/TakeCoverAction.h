#pragma once
#include "OldAction.h"
#include "Option.h"
class TakeCoverAction :
    public OldAction
{
public:
	TakeCoverAction(Agent* cover, Agent* enemy);
	TakeCoverAction(TakeCoverAction&) = default;
	TakeCoverAction(TakeCoverAction&&) = default;
	void onActionStart(Agent* currentA) override;
	void onActionUpdate(Agent* currentA, float dt, AgentManager* am) override;
	void onActionFinished(Agent* currentA) override;
	bool isFinished() override;

	static std::unique_ptr<OldAction> create(Option* data) {
		return std::make_unique<TakeCoverAction>(data->getParameter<Agent*>("Cover"),data->getParameter<Agent*>("Enemy"));
	}
private:
	Agent* m_cover;
	Agent* m_enemy;
	float m_cover_value;
	sf::Vector2f m_cover_pos;
	int stayInCover = 0;
	float distance;
};

