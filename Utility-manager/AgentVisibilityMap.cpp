#include "AgentVisibilityMap.h"
#include <algorithm>

AgentVisibilityMap::AgentVisibilityMap()
{
}

void AgentVisibilityMap::init(uint32_t tiles_x, uint32_t tiles_y, uint32_t tile_size_x, uint32_t tile_size_y)
{

}

TacticalMap AgentVisibilityMap::compute(Costfield cmap,InputEntity entity)
{
	TacticalMap tm;
	tm.init(cmap.getData().getSizeX(), cmap.getData().getSizeY(), 0.f);

	switch (entity.direction)
	{
	case InputEntity::n:
		prepMap(tm, { -1, -1 }, entity);
		prepMap(tm, { 1, -1 }, entity);
		addObstacle(tm, cmap);
		m_mirror_x = -1;
		m_mirror_y = -1;
		visibilityCone(tm, { 1,1 }, { 0,1 }, entity.pos);
		visibilityCone(tm, { 1,1 }, { 1,0 }, entity.pos);
		cutCone(tm, entity, true);
		m_mirror_x = 1;
		m_mirror_y = -1;
		visibilityCone(tm, { 1,1 }, { 0,1 }, entity.pos);
		visibilityCone(tm, { 1,1 }, { 1,0 }, entity.pos);
		cutCone(tm, entity, true);
		break;
	case InputEntity::o:
		prepMap(tm, { 1, -1 }, entity);
		prepMap(tm, { 1, 1 }, entity);
		addObstacle(tm, cmap);
		m_mirror_x = 1;
		m_mirror_y = -1;
		visibilityCone(tm, { 1,1 }, { 0,1 }, entity.pos);
		visibilityCone(tm, { 1,1 }, { 1,0 }, entity.pos);
		cutCone(tm, entity);
		m_mirror_x = 1;
		m_mirror_y = 1;
		visibilityCone(tm, { 1,1 }, { 0,1 }, entity.pos);
		visibilityCone(tm, { 1,1 }, { 1,0 }, entity.pos);
		cutCone(tm, entity);
		break;
	case InputEntity::s:
		prepMap(tm, { 1, 1 }, entity);
		prepMap(tm, { -1, 1 }, entity);
		addObstacle(tm, cmap);
		m_mirror_x = 1;
		m_mirror_y = 1;
		visibilityCone(tm, { 1,1 }, { 0,1 }, entity.pos);
		visibilityCone(tm, { 1,1 }, { 1,0 }, entity.pos);
		cutCone(tm, entity, true);
		m_mirror_x = -1;
		m_mirror_y = 1;
		visibilityCone(tm, { 1,1 }, { 0,1 }, entity.pos);
		visibilityCone(tm, { 1,1 }, { 1,0 }, entity.pos);
		cutCone(tm, entity, true);
		break;
	case InputEntity::w:
		prepMap(tm, { -1, 1 }, entity);
		prepMap(tm, { -1, -1 }, entity);
		addObstacle(tm, cmap);
		m_mirror_x = -1;
		m_mirror_y = 1;
		visibilityCone(tm, { 1,1 }, { 0,1 }, entity.pos);
		visibilityCone(tm, { 1,1 }, { 1,0 }, entity.pos);
		cutCone(tm, entity);
		m_mirror_x = -1;
		m_mirror_y = -1;
		visibilityCone(tm, { 1,1 }, { 0,1 }, entity.pos);
		visibilityCone(tm, { 1,1 }, { 1,0 }, entity.pos);
		cutCone(tm, entity);
		break;
	case InputEntity::no:
		m_mirror_x = 1;
		m_mirror_y = -1;
		prepMap(tm, { m_mirror_x, m_mirror_y }, entity);
		addObstacle(tm, cmap);

		visibilityCone(tm, { 1,1 }, { 0,1 }, entity.pos);
		visibilityCone(tm, { 1,1 }, { 1,0 }, entity.pos);
		break;
	case InputEntity::so:
		m_mirror_x = 1;
		m_mirror_y = 1;
		prepMap(tm, { m_mirror_x, m_mirror_y }, entity);
		addObstacle(tm, cmap);

		visibilityCone(tm, { 1,1 }, { 0,1 }, entity.pos);
		visibilityCone(tm, { 1,1 }, { 1,0 }, entity.pos);
		break;
	case InputEntity::sw:
		m_mirror_x = -1;
		m_mirror_y = 1;
		prepMap(tm, { m_mirror_x, m_mirror_y }, entity);
		addObstacle(tm, cmap);

		visibilityCone(tm, { 1,1 }, { 0,1 }, entity.pos);
		visibilityCone(tm, { 1,1 }, { 1,0 }, entity.pos);
		break;
	case InputEntity::nw:
		m_mirror_x = -1;
		m_mirror_y = -1;
		prepMap(tm, { m_mirror_x, m_mirror_y }, entity);
		addObstacle(tm, cmap);

		visibilityCone(tm, { 1,1 }, { 0,1 }, entity.pos);
		visibilityCone(tm, { 1,1 }, { 1,0 }, entity.pos);
		break;
	default:
		m_mirror_x = 1;
		m_mirror_y = 1;
		prepMap(tm, { m_mirror_x, m_mirror_y }, entity);
		addObstacle(tm, cmap);

		visibilityCone(tm, { 1,1 }, { 0,1 }, entity.pos);
		visibilityCone(tm, { 1,1 }, { 1,0 }, entity.pos);
		break;
	}

	//addObstacle(tm, cmap);
	
	//visibilityCone(tm, { 1,1 }, { 0,1 }, entity.pos);
	//visibilityCone(tm, { 1,1 }, { 1,0 }, entity.pos);

	//visibilityCone(tm, { 1,0 }, { 0,1 }, entity.pos);

	
	//visibilityCone(tm, { 1,1 }, { 0,1 });
	//visibilityCone(tm, { 1,1 }, { 1,0 });

	return tm;
}

TacticalMap AgentVisibilityMap::compute360(Costfield cmap, InputEntity entity)
{	
	TacticalMap tm;
	tm.init(cmap.getData().getSizeX(), cmap.getData().getSizeY(), 0.f);
	
	
	prepMap(tm, { 1, 1 }, entity);
	
	prepMap(tm, { 1, -1 }, entity);
	
	prepMap(tm, { -1, 1 }, entity);
	
	prepMap(tm, { -1, -1 }, entity);
	
	addObstacle(tm, cmap);

	m_mirror_x = 1;
	m_mirror_y = 1;
	visibilityCone(tm, { 1,1 }, { 0,1 }, entity.pos);
	visibilityCone(tm, { 1,1 }, { 1,0 }, entity.pos);
	m_mirror_x = 1;
	m_mirror_y = -1;
	visibilityCone(tm, { 1,1 }, { 0,1 }, entity.pos);
	visibilityCone(tm, { 1,1 }, { 1,0 }, entity.pos);
	m_mirror_x = -1;
	m_mirror_y = 1;
	visibilityCone(tm, { 1,1 }, { 0,1 }, entity.pos);
	visibilityCone(tm, { 1,1 }, { 1,0 }, entity.pos);
	m_mirror_x = -1;
	m_mirror_y = -1;
	visibilityCone(tm, { 1,1 }, { 0,1 }, entity.pos);
	visibilityCone(tm, { 1,1 }, { 1,0 }, entity.pos);
	return tm;
}

void AgentVisibilityMap::visibilityCone(TacticalMap& tm, VecInt2D u_dir, VecInt2D v_dir, Vec2D start_pos)
{
	int distance = 10;
	int mirror_x = m_mirror_x;
	int mirror_y = m_mirror_y;

	VecInt2D u  = { u_dir.x,u_dir.y };
	VecInt2D v = { v_dir.x,v_dir.y };
	VecInt2D start = { start_pos.x, start_pos.y };
	VecInt2D dim = { distance+ 1, distance + 1 };

	int m = 0, k = 0;
	VecInt2D current_pos = { 0,0 };

	auto const size_x = tm.getSizeX();
	auto const size_y = tm.getSizeY();
	while (current_pos.x < dim.x&&current_pos.y<dim.y)
	{
		while (current_pos.x < dim.x && current_pos.y < dim.y)
		{
			if (current_pos.x != 0 || current_pos.y != 0)
			{
				int pos_x = start.x + current_pos.x * mirror_x;
				int pos_y = start.y + current_pos.y * mirror_y;
				if (!(pos_y < 0 || pos_x < 0 || pos_y >= size_y || pos_x >= size_x))
				{

					int pos_minus_u_x = start.x + std::max(0, (current_pos.x - u.x)) * mirror_x;
					int pos_minus_u_y = start.y + std::max(0, (current_pos.y - u.y)) * mirror_y;
					int pos_minus_v_x = start.x + std::max(0, (current_pos.x - v.x)) * mirror_x;
					int pos_minus_v_y = start.y + std::max(0, (current_pos.y - v.y)) * mirror_y;

					tm.at(pos_x, pos_y) *= (m * tm.at(pos_minus_u_x, pos_minus_u_y) +
						k * tm.at(pos_minus_v_x, pos_minus_v_y)) / (m + k);
				}
			}
			k++;
			current_pos.x += v.x;
			current_pos.y += v.y;
		}
		m++;
		k = 0;
		current_pos.x = m * u.x;
		current_pos.y = m * u.y;
	}
}

void AgentVisibilityMap::addObstacle(TacticalMap& tm, Costfield cmap)
{
	for (auto x = 0u; x < tm.getSizeX(); x++)
	{
		for (auto y = 0u; y < tm.getSizeY(); y++)
		{
			auto value = cmap.getData().at(x, y);
			if (value == 255||value==250||value==200)
			{
				tm.at(x, y) = 0;
			}
			//add different visibilities here bsp tree has 244 cost and 0.5 vis
		}
	}

	//tm.at(11, 15) = 0.5;
	//tm.at(12, 15) = 0.5;
	//tm.at(13, 15) = 0.5;

}

void AgentVisibilityMap::prepMap(TacticalMap& tm, VecInt2D dir_vec, InputEntity entity)
{
	
	float end_x = (entity.pos.x + entity.visibility_range * dir_vec.x);
	float end_y = (entity.pos.y + entity.visibility_range * dir_vec.y);
	float start_x = entity.pos.x;
	float start_y = entity.pos.y;

	end_x = std::min(float(tm.getSizeX() - 1), std::max(end_x, 0.f));
	end_y = std::min(float(tm.getSizeY() - 1), std::max(end_y, 0.f));
	if (end_x < entity.pos.x)
	{
		std::swap(end_x, start_x);
	}
		
	if (end_y < entity.pos.y)
	{
		std::swap(end_y, start_y);
	}

	for (auto x = start_x; x <= end_x; x++)
	{
		for (auto y = start_y; y <= end_y; y++)
		{
			tm.at(x, y) = 1;
		}
	}
}

void AgentVisibilityMap::cutCone(TacticalMap& tm, InputEntity entity, bool invert )
{
	int ox = static_cast<int>(entity.pos.x);
	int oy = static_cast<int>(entity.pos.y);

	for (int dx = 0; dx <= entity.visibility_range; dx++)
	{
		for (int dy = 0; dy <= entity.visibility_range; dy++)
		{
			// Only keep cells inside the triangle defined by dx >= dy
			if (invert ? (dy < dx) : (dy > dx))
			{
				int tx = ox + dx * m_mirror_x;
				int ty = oy + dy * m_mirror_y;

				if ((tx >= 0 && tx < tm.getSizeX() && ty >= 0 && ty < tm.getSizeY()))
				{
					tm.at(tx, ty) = 0.f;
				}
			}
		}
	}
}

InputEntity::Direction directionFromRotation(float rot)
{
	rot = fmod(rot + 180, 360.0f);
	if (rot < 0) {
		rot += 360.0f;
	}
	int rounded = static_cast<int>(round(rot / 45.0f) * 45);
	switch (rounded) {
	case 0:
		return InputEntity::n;
	case 45:
		return InputEntity::no;
	case 90:
		return InputEntity::o;
	case 135:
		return InputEntity::so;
	case 180:
		return InputEntity::s;
	case 225:
		return InputEntity::sw;
	case 270:
		return InputEntity::w;
	case 315:
		return InputEntity::nw;
	default:
		return InputEntity::n;
	}
}
