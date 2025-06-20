#include "IReasoner.h"

#include "imgui.h"

void IReasoner::addOption(Option::ptr option) { m_options.push_back(option); }

void IReasoner::drawDebug()
{
	for (auto& option : m_options)
	{
		if (ImGui::CollapsingHeader(option->getName().c_str()))
		{
			option->DrawDebugUi();
		}
	}
}
