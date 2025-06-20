#include "LookAroundAction.h"


void LookAroundAction::onActionStart(BlackboardManager& bm, IEngineDataOutput* cmd, IEngineDataInput* data)
{
	rotation = data->getAgentRotation(m_agent);
	deltaTime = data->getDeltaTime(m_agent);
}

void LookAroundAction::onActionUpdate(BlackboardManager& bm, IEngineDataOutput* cmd)
{
	rotation += 90.f*deltaTime;

	if (rotation >= 360.0f) rotation -= 360.0f;
	cmd->rotate(m_agent, rotation);
}

void LookAroundAction::onActionFinished(BlackboardManager& bm, IEngineDataOutput*)
{

}

std::unique_ptr<IAction> LookAroundAction::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<LookAroundAction>();
	return result;
}

float LookAroundAction::clamp_rotation(float rot)
{
	if (rot < 0)
		rot += 360;
	else if (rot >= 360)
		rot -= 360;

	return rot;
}
