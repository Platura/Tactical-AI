#include "MapManager.h"
#include "imgui.h"
#include "MapDebugDisplay.h"
#include "EngineDebugData.h"
MapManager::MapManager()
{
}

Flowfield MapManager::computeFlowfield(const std::vector<sf::Vector2f>& targets)
{
	const auto tile_size = m_tilemap.getTileSize();

	Flowfield computedFlowfield;
	computedFlowfield.init(m_tilemap.get_map_data(), m_cost.getData(), sf::Vector2f(tile_size));
	
	std::vector<sf::Vector2i> target_grid;
	for (auto el : targets)
	{
		target_grid.push_back(computedFlowfield.worldToGridPos(el));
	}

	computedFlowfield.integrate(target_grid);
	return computedFlowfield;
}

Flowfield MapManager::computeFlowfield(const std::vector<sf::Vector2f>& targets, Costfield const& cost)
{
	const auto tile_size = m_tilemap.getTileSize();

	Flowfield computedFlowfield;
	computedFlowfield.init(m_tilemap.get_map_data(), cost.getData(), sf::Vector2f(tile_size));

	std::vector<sf::Vector2i> target_grid;
	for (auto el : targets)
	{
		target_grid.push_back(computedFlowfield.worldToGridPos(el));
	}

	computedFlowfield.integrate(target_grid);
	return computedFlowfield;
}


void MapManager::init(std::string path, const std::vector<sf::Vector2i>& targets)
{
	m_tilemap.read_map_from_file(path);

	const auto tile_size = m_tilemap.getTileSize();
	const auto tile_count = m_tilemap.getMapSize();
	m_grid.resize(tile_size.x, tile_size.y, tile_count.x, tile_count.y);

	m_cost.init(m_tilemap.get_map_data());
	m_flow.init(m_tilemap.get_map_data(), m_cost.getData(), sf::Vector2f(tile_size));
	m_flow.integrate(targets);

}

enum FieldDrawMode {
	VALUES,
	COLOR,
	COUNT
} current_draw_mode;

std::vector<std::string_view> draw_mode_names{
	"Values",
	"Color"
};

void MapManager::draw(sf::RenderTarget& rt)
{
	ImGui::Begin("FlowField Controls");
	ImGui::SeparatorText("Rendering");
	static bool draw_grid = true;
	ImGui::Checkbox("Draw Grid", &draw_grid);
	static bool draw_cost = false;
	ImGui::Checkbox("Draw Costs", &draw_cost);
	static bool draw_integration = false;
	ImGui::Checkbox("Draw Integration", &draw_integration);
	static bool draw_flowfield = false;
	ImGui::Checkbox("Draw FlowField", &draw_flowfield);
	static bool draw_tactical_map = false;
	ImGui::Checkbox("Draw Tacticalmap", &draw_tactical_map);



	if (draw_tactical_map)
	{
		auto current = EngineDebugData::getInstance()->getCurrentMap();
		if (ImGui::BeginCombo("Map", current.c_str()))
		{
			for (auto const& [key, map] : EngineDebugData::getInstance()->getData())
			{
				if(ImGui::Selectable(key.c_str(), key == current ))
					EngineDebugData::getInstance()->setCurrenMap(key);
			}
			ImGui::EndCombo();
		}
		if (ImGui::BeginCombo("Draw Mode", draw_mode_names[(size_t)current_draw_mode].data()))
		{
			for (size_t i = 0; i < FieldDrawMode::COUNT; ++i)
			{
				if (ImGui::Selectable(draw_mode_names[i].data(), i == current_draw_mode))
					current_draw_mode = (FieldDrawMode)i;
			}
			ImGui::EndCombo();
		}
	}

	rt.draw(m_tilemap);
	
	
	if (draw_grid)
	{
		rt.draw(m_grid);
	}

	if (draw_cost)
	{
		m_grid.drawValuesOnGrid(rt, m_cost.getData());
	}

	if(draw_flowfield || draw_integration)
	{
		auto& data = MapDebugDisplay::getInstance()->getData();
		auto current_flowfield_name = MapDebugDisplay::getInstance()->getCurrentName();

		if (ImGui::BeginCombo("Map", current_flowfield_name.c_str()))
		{
			for (auto const& [name, map] : data)
			{
				if (ImGui::Selectable(name.c_str(), name == current_flowfield_name))
					MapDebugDisplay::getInstance()->setCurrentMap(map);
			}
			ImGui::EndCombo();
		}

		if (MapDebugDisplay::getInstance()->isValid(current_flowfield_name))
		{
	
			ImGui::Text(fmt::format("Current Map {}", MapDebugDisplay::getInstance()->getCurrentName()).c_str());

			auto current_flowfield = MapDebugDisplay::getInstance()->getCurrentMap();
			if (draw_integration)
			{
				m_grid.drawValuesOnGrid(rt, current_flowfield->getIntegrationData());

			}
			if(draw_flowfield)
				m_grid.drawField(rt, current_flowfield->getData());
		}
	}
	
	if (draw_tactical_map && EngineDebugData::getInstance()->hasValidSelection())
	{
		auto field = EngineDebugData::getInstance()->getSelectedMap();
		if (current_draw_mode == FieldDrawMode::VALUES)
		{
			m_grid.drawValuesOnGrid(rt,*field);
		}
		else if (current_draw_mode == FieldDrawMode::COLOR)
		{
			m_grid.drawColorOnGrid(rt, *field);

		}
	}

	ImGui::End();
}
