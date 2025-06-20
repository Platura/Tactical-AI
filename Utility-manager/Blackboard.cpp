#include "Blackboard.h"
#include "EngineDebugData.h"
#include "imgui.h"
#include <fmt/format.h>
#include <fmt/ranges.h>

void Blackboard::drawDebug()
{
	//ImGui::PushID(this);
	ImGui::BeginTable("Blacboard", 2);

	for (auto const& [key, value] : m_data)
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();

		ImGui::Text(key.c_str());
		ImGui::TableNextColumn();

		auto str = std::visit([](auto&& arg)
            {
                using T = std::decay_t<decltype(arg)>;
				if constexpr (std::is_same_v<T, aiNone>)
					return std::string{ "None" };
				else if constexpr (std::is_same_v<T, aiInt>)
					return fmt::format("{}", arg);
				else if constexpr (std::is_same_v<T, aiUInt>)
					return fmt::format("{}", arg);
				else if constexpr (std::is_same_v<T, aiFloat>)
					return fmt::format("{}", arg);
				else if constexpr (std::is_same_v<T, aiPosition>)
					return fmt::format("{}, {}", arg.x, arg.y);
				else if constexpr (std::is_same_v<T, uint64_t>)
					return fmt::format("{}", arg);
				else if constexpr (std::is_same_v<T, std::vector<std::pair<uint32_t, uint32_t>>>)
					return fmt::format("{}", fmt::join(arg, ", "));
				else if constexpr (std::is_same_v<T, std::vector<aiAgentId>>)
					return fmt::format("{}", fmt::join(arg, ", "));
				else if constexpr (std::is_same_v<T, InfluenceMap>)
					return fmt::format("InfluenceMap size: {}x{}", arg.getField().getSizeX(), arg.getField().getSizeY());
				else if constexpr (std::is_same_v<T, TacticalMap>)
					return fmt::format("TacticalMap size: {}x{}", arg.getSizeX(), arg.getSizeY());
				else if constexpr (std::is_same_v<T, Costfield>)
					return fmt::format("Costfield size: {}x{}", arg.getData().getSizeX(), arg.getData().getSizeY());
				else
                    static_assert(false, "non-exhaustive visitor!");
            }, value);

		ImGui::Text(str.c_str());

		std::visit([](auto&& arg) {
			using T = std::decay_t<decltype(arg)>;
			if constexpr (std::is_same_v<T, InfluenceMap>)
			{
				ImGui::SameLine();
				if (ImGui::Button("Select"))
				{
					EngineDebugData::getInstance()->setCurrenMap((Field<float>*) & arg.getField());
				}
			}
			else if constexpr (std::is_same_v<T, TacticalMap>)
			{
				ImGui::SameLine();
				if (ImGui::Button("Select"))
				{
					EngineDebugData::getInstance()->setCurrenMap((Field<float>*) & arg);
				}
			}
		}, value);

	}

	ImGui::EndTable();
	//ImGui::PopID();

}

void Blackboard::registerTacticalMap(TacticalMap* t, std::string key)
{
	EngineDebugData::getInstance()->register_map((Field<float>*)t, key);

}

values valuesFromJson(json const& value)
{
	if (value.is_number_float())
	{
		return value.get<float>();
	}
	else if (value.is_number())
	{
		return value.get<aiInt>();
	}
	else if (value.is_object())
	{
		if (value.contains("x") && value.contains("y"))
		{
			return Vec2D(value["x"], value["y"]);
		}
	}
}
