#pragma once
#include "IConsideration.h"
class ConsiderationArithmeticAverage :
    public IConsideration
{
public:
    //berechnet den Arithmetischen Mittelwert aller Considerations
    ConsiderationArithmeticAverage(std::vector<ConsiderationPtr> considerations);
    float compute(BlackboardManager& bm) override;
    void DrawDebugUiChild() override;
private:
    std::vector<ConsiderationPtr> m_considerations;
    float score=0;
};

