#pragma once
#include "TacticalMap.h"
#include "Field.h"
#include "Costfield.h"
#include "Types.hpp"
#include <vector>



struct InputEntity
{
	Vec2D pos;
	enum Direction { n, no, o, so, s, sw, w, nw };
	Direction direction;
	float visibility_range;
};


InputEntity::Direction directionFromRotation(float rot);
class AgentVisibilityMap
{
	//A map that contains the visibility of selected Agents
	//uses counting instead of a raycast
public:
	AgentVisibilityMap();
	void init(uint32_t tiles_x, uint32_t tiles_y, uint32_t tile_size_x, uint32_t tile_size_y);
	TacticalMap compute(Costfield cmap, InputEntity entity);
	TacticalMap compute360(Costfield cmap, InputEntity entity);
	void visibilityCone(TacticalMap& tm, VecInt2D u_dir, VecInt2D v_dir, Vec2D start_pos);
	void addObstacle(TacticalMap& tm, Costfield cmap);
	void prepMap(TacticalMap& tm, VecInt2D dir_vec, InputEntity entity);
	void cutCone(TacticalMap& tm, InputEntity entity, bool invert = false);
private:
	int m_mirror_x;
	int m_mirror_y;
	
};

