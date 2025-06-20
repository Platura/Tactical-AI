#pragma once
#include "Field.h"
#include "Costfield.h"
#include "Types.hpp"
#include <map>
#include <vector>

struct AgentEntity
{
	Vec2D pos;
	uint32_t type;
};
class InfluenceMap
{
private:
	std::map<uint32_t, Field<float>> m_linear_templates;
	Field<float> m_threat_map_max;
	Field<float> m_threat_map_sum;
	Field<float> m_save_points;
	Field<float> m_proximity_map;
	int m_tile_size_x;
	int m_tile_size_y;
public:
	InfluenceMap();
	void init(uint32_t tiles_x, uint32_t tiles_y, uint32_t tile_size_x, uint32_t tile_size_y);
	void compute(std::vector<AgentEntity> const& entities, const Costfield& cmap);
	bool isObstructed(int x0, int y0, int x1, int y1, const Costfield& cmap);
	void createLinearTemplate(uint32_t type, float distance);
	void createExpoTemplate(uint32_t type, float distance);
	void consoleOut(Field<float> field);

	auto const& getField() const { return m_threat_map_max; }
	auto & getField()  { return m_threat_map_max; }

	auto const& getFieldSum() const { return m_threat_map_sum; }
	auto& getFieldSum() { return m_threat_map_sum; }

	auto const& getFieldSave() const { return m_save_points; }
	auto& getFieldSave() { return m_save_points; }

	float at(float x, float y) const;
};
