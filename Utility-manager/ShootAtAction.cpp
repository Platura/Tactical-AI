#include "ShootAtAction.h"
#include <ctime>

void ShootAtAction::onActionStart(BlackboardManager& bm, IEngineDataOutput*cmd, IEngineDataInput*data)
{
	auto shot_target = bm.getAgentBlackboard(m_agent).getValue<aiAgentId>("agent_target");
	if (!shot_target.has_value())
	{
		return;
	}
	auto maybe_pos = bm.getAgentBlackboard(shot_target.value()).getValue<aiPosition>("position");
	if (!maybe_pos.has_value())
	{
		return;
	}
	shot_pos = maybe_pos.value();
	auto accuracy = 0.7;
	float randomValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	auto agent_ammunition = bm.getAgentBlackboard(m_agent).getValue<aiInt>("ammunition");
	auto damage = 30;
	if (!agent_ammunition.has_value())
	{
		ammo = data->getAgentAmmunition(m_agent);
	}
	else
	{
		ammo = agent_ammunition.value();
	}
	auto covered = bm.getAgentBlackboard(shot_target.value()).getValue<aiFloat>("cover_value");
	if (covered.has_value())
	{
		cmd->setCover(shot_target.value(), covered.value());
	}
	if (randomValue <= accuracy)
	{
		cmd->dealDamage(shot_target.value(), damage);
	}
	
}

void ShootAtAction::onActionUpdate(BlackboardManager& bm, IEngineDataOutput*cmd)
{	
	cmd->shootAt(m_agent, shot_pos);
	ammo--;
	m_isFinished = true;
}

void ShootAtAction::onActionFinished(BlackboardManager& bm, IEngineDataOutput*)
{
	*m_ammunition.getPtr<aiInt>(bm) = ammo;
}

std::unique_ptr<IAction> ShootAtAction::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<ShootAtAction>();

	if (parameter.contains("ammunition"))
	{
		result->m_ammunition.init(agent, team, parameter["ammunition"]);
	}

	return result;
}
