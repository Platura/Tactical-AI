#pragma once
#include "TacticalMap.h"
#include "AgentVisibilityMap.h"
#include <vector>

class AmbushMap
{
public:
	AmbushMap() = default;
	TacticalMap compute(std::vector<TacticalMap> agent_vis, TacticalMap target_vis);
	//vismap von feinden combinieren
	//invert
	//vis compute360()
private:

};

