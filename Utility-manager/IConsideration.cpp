#include "IConsideration.h"

#include "imgui.h"


void IConsideration::DrawDebugUi() {

	ImGui::PushID(this);
	ImGui::SeparatorText(m_name.c_str());
	ImGui::Text("Last Value: %f", m_last_value);
	ImGui::Text("Last Value (weight): %f", getLastValueWeight());
	DrawDebugUiChild();

	ImGui::PopID();
}

