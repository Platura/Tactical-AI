#include "TakeAimAction.h"


void TakeAimAction::onActionStart(BlackboardManager& bm, IEngineDataOutput* cmd, IEngineDataInput*data)
{
	auto position = bm.getAgentBlackboard(m_agent).getValue<aiPosition>("position").value();
	auto target_id = bm.getAgentBlackboard(m_agent).getValue<aiAgentId>("agent_target").value();
	auto target_pos = bm.getAgentBlackboard(target_id).getValue<aiPosition>("position");
	if (!target_pos.has_value())
	{
		m_isFinished = true;
		return;
	}
	Vec2D direction = { target_pos.value().x - position.x,  target_pos.value().y - position.y};
	angle = std::atan2(-direction.x, direction.y) * 180 / 3.14f;
	agent_rotation = data->getAgentRotation(m_agent);
	angle = clamp_rotation(angle);
	agent_rotation = clamp_rotation(agent_rotation);

	delta_rotation = angle - agent_rotation;

	rot_direction = delta_rotation < 180 ? 1 : -1;
	delta_time = data->getDeltaTime(m_agent);

	
}

void TakeAimAction::onActionUpdate(BlackboardManager& bm, IEngineDataOutput* cmd)
{
	delta_rotation = std::abs(angle - agent_rotation);


	float rotation_speed = 90.0f;
	constexpr float tick_time = 1 / 30.f;
	auto tick_rotation = rotation_speed * delta_time;
	agent_rotation += std::min(tick_rotation, delta_rotation) * rot_direction;

	agent_rotation = clamp_rotation(agent_rotation);

	cmd->rotate(m_agent, agent_rotation);

	if (std::abs(angle - agent_rotation) <= 1)
		m_isFinished = true;
}

void TakeAimAction::onActionFinished(BlackboardManager& bm, IEngineDataOutput*)
{
	
}

std::unique_ptr<IAction> TakeAimAction::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<TakeAimAction>();

	if (parameter.contains("direction"))
	{
		result->m_direction.init(agent, team, parameter["direction"]);
	}

	return result;
}

float TakeAimAction::clamp_rotation(float rot)
{
	if (rot < 0)
		rot += 360;
	else if (rot >= 360)
		rot -= 360;

	return rot;
}
