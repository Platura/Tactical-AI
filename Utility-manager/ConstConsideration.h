#pragma once
#include "IConsideration.h"


class ConstConsideration : public IConsideration
{

	float value = 0;
public:
	ConstConsideration() = default;
	ConstConsideration(float value) : value(value) {};

	float compute(BlackboardManager& bm) override { return value; }

	static ConsiderationPtr Create(float value) {
		return std::make_unique<ConstConsideration>(value);
	}
	/*
	void DrawDebugUiChild() override
	{
		if(ImGui::TreeNode("Const Consideration"))
		{
			ImGui::SliderFloat("Value", &value,  0.f, 1.f);
			ImGui::TreePop();
		}
		
	};*/

	static std::unique_ptr<IConsideration> create(json const& parameter, aiAgentId const& agent, aiTeamId const& team);

};