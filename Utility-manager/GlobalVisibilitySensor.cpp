#include "GlobalVisibilitySensor.h"
#include "GlobalVisibilityMap.h"
#include "EngineDebugData.h"

std::unique_ptr<ISensor> GlobalVisibilitySensor::create(json const& parameter)
{
	auto ptr = std::make_unique<GlobalVisibilitySensor>();

	if (parameter.contains("field_name"))
	{
		ptr->m_field_name = parameter["field_name"];
	}
	return std::move(ptr);
}

void GlobalVisibilitySensor::update(BlackboardManager& bm, IEngineDataInput* data)
{

	auto bb_ptr = bm.getGlobal().getValuePtr<TacticalMap>(m_field_name);
	if (isFirstTime)
	{
		EngineDebugData::getInstance()->register_map(bb_ptr, fmt::format("GlobalVis"));
		auto cmap = data->getCostField();
		GlobalVisibilityMap global_vis;
		*bb_ptr = global_vis.compute(cmap);
		bm.getGlobal().setValue("global_vis", *bb_ptr);
		isFirstTime = false;
	}
	
}
