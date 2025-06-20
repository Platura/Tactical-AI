#include "ConsiderationEnemyDistance.h"
#include "MathFunctions.h"

ConsiderationEnemyDistance::ConsiderationEnemyDistance()
{
}

float ConsiderationEnemyDistance::compute(BlackboardManager& bm)
{
    //If the enemy is too far away it makes no sense to attack so the score is 0;
    //If the enemy is in range the score should be higher the closer the enemy
    //Linear from 0 = 1 to 3 = 0
    //Formel (value-min)/(max-min)
    if (m_enemyDistance > 3)
        return 0;
    float score = getPartialLinear(m_enemyDistance, 0, 3);
    return score;
}

void ConsiderationEnemyDistance::DrawDebugUiChild()
{
    if (ImGui::TreeNode("ConsiderationMelee"))
    {
        //ImGui::LabelText("Value", "%f", compute());
        ImGui::SliderFloat("enemyDistance", &m_enemyDistance, 0, 10);
        ImGui::TreePop();
    }
    
}
