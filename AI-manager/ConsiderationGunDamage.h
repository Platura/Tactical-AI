#pragma once
#include "IConsideration.h"
class ConsiderationGunDamage :
    public IConsideration
{
public:
	ConsiderationGunDamage();
	float compute(BlackboardManager& bm) override;
	void DrawDebugUiChild() override;
private:
};

