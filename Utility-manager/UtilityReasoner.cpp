#include "UtilityReasoner.h"
#include <imgui.h>
#include <algorithm>
#include <fmt/format.h>

/*void  UtilityReasoner::addOption(Option& option)
{
    m_options.emplace_back(option);
}*/


void UtilityReasoner::update(BlackboardManager& bm)
{
    //std::vector<Option*> result;
    int bestResult=0;
    for (int i = 0; i < m_options.size(); ++i)
    {
        auto& el = m_options[i];
        el->compute(bm);
        if(el->getLastValue() > m_options[bestResult]->getLastValue())
        bestResult=i;
    }

    m_bestOption = bestResult;
}

std::unique_ptr<IReasoner> UtilityReasoner::create(json const& parameter)
{
    auto ptr = std::make_unique<UtilityReasoner>();
    if (parameter.contains(""))
    {

    }
    return ptr;
}

void UtilityReasoner::DrawDebugUi()
{
    //ImGui::Begin(fmt::format("Reasoner {}", m_name).c_str());
    
    for (auto& el : m_options)
    {
        if (ImGui::CollapsingHeader(fmt::format("Action {}", el->getName()).c_str()))
        {
            el->DrawDebugUi();
        }
    }

    //ImGui::End();
}
