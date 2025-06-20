#include "ComputeHiddenCoverAction.h"
#include "CoverMap.h"
void ComputeHiddenCoverAction::onActionStart(BlackboardManager& bm, IEngineDataOutput* cmd, IEngineDataInput*data)
{
	auto cmap = data->getCostField();
	auto global_vis = bm.getGlobal().getValue<TacticalMap>("global_vis").value();
	CoverMap cover;
	cover_map = cover.compute(cmap);
	cover_map*=global_vis.invert();
	//Method for selecting coverpoint
	//Take the nearest cover and select the highest value point
}

void ComputeHiddenCoverAction::onActionUpdate(BlackboardManager& bm, IEngineDataOutput* cmd)
{
	m_isFinished = true;
}

void ComputeHiddenCoverAction::onActionFinished(BlackboardManager& bm, IEngineDataOutput* cmd)
{
	*m_cover.getPtr<TacticalMap>(bm) = cover_map;
}

std::unique_ptr<IAction> ComputeHiddenCoverAction::create(json const& parameter, aiAgentId const& agent, aiTeamId const& team)
{
	auto result = std::make_unique<ComputeHiddenCoverAction>();

	if (parameter.contains("cover"))
	{
		result->m_cover.init(agent, team, parameter["cover"]);
	}

	return result;
}