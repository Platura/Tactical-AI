#include "ConsiderationAmmunitionReserve.h"
#include "MathFunctions.h"

ConsiderationAmmunitionReserve::ConsiderationAmmunitionReserve(Agent* a):m_agent(a)
{
	m_currentAmmo = m_agent->getAmmunition();
	m_maxAmmo = m_agent->getMaxAmmunition();
	
}

float ConsiderationAmmunitionReserve::compute(BlackboardManager& bm)
{
	//1-(x/m)^k
	m_currentAmmo = m_agent->getAmmunition();
	m_maxAmmo = m_agent->getMaxAmmunition();
	float score = 1 - getQuadratic((float)m_currentAmmo, (float)m_maxAmmo, m_k);
	return score;
}

void ConsiderationAmmunitionReserve::DrawDebugUiChild()
{
	if (ImGui::TreeNode("ConsiderationAmmunitionReserve"))
	{
		//ImGui::LabelText("Value", "%f", compute());
		ImGui::SliderInt("currentAmmo", &m_currentAmmo, 0, m_maxAmmo);
		ImGui::SliderFloat("k", &m_k, -5, 5);
		ImGui::TreePop();
	}
}
