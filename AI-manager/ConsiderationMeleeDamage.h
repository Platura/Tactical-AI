#pragma once
#include "IConsideration.h"
class ConsiderationMeleeDamage :
    public IConsideration
{
public:
	ConsiderationMeleeDamage();
	float compute(BlackboardManager& bm) override;
	void DrawDebugUiChild() override;
private:
};

