#include "ConsiderationArithmeticAverage.h"
#include "imgui.h"

ConsiderationArithmeticAverage::ConsiderationArithmeticAverage(std::vector<ConsiderationPtr> considerations)
{
	m_considerations = considerations;
}

float ConsiderationArithmeticAverage::compute(BlackboardManager& bm)
{
	//für gewichtung * m_weight nehmen
	score = 0;
	for (auto& el : m_considerations)
	{
		score += el->compute(bm);
	}
	score /= m_considerations.size();
	return score;
}

void ConsiderationArithmeticAverage::DrawDebugUiChild()
{
	if (ImGui::TreeNode("ConsiderationArithmeticAverage"))
	{
		for (auto& el : m_considerations)
		{
			el->DrawDebugUi();
			//ImGui::LabelText("Input", "%f", el->compute());
		}
		//ImGui::LabelText("Value", "%f", compute());
		//ImGui::SliderFloat("enemyDistance", &m_weight, 0, 10);
		ImGui::TreePop();
	}

}
