#pragma once
#include "TacticalMap.h"
class SaveFrontMap
{
public:
	//A Map that evaluates positions close to the front on how save they are
	SaveFrontMap();
	TacticalMap compute(aiPosition pos, TacticalMap cover, TacticalMap spotted);
	void addTemplate(int x, int y, TacticalMap& tm);
private:

};

