#pragma once
#include <iostream>
#include <functional>
#include <string>
#include "IFunction.h"
#include "IdentityFunction.h"
#include "BlackboardManager.h"


class IConsideration
{
	IFunction::ptr m_weight_function = IdentityFunction::create({});

	float m_last_value;

	std::string m_name;
protected:
	aiAgentId m_agent;
	aiTeamId m_team;
public:
	void initIds(aiAgentId agent, aiTeamId team)
	{
		m_agent = agent;
		m_team = team;
	}

	virtual float compute(BlackboardManager& bm) = 0;
	float compute_with_weight(BlackboardManager& bm)
	{
		m_last_value = compute(bm);
		return m_weight_function->compute(m_last_value);
	}

	void DrawDebugUi();
	virtual void DrawDebugUiChild() {};


	float getLastValue() const { return m_last_value; }
	float getLastValueWeight() const { return m_weight_function->compute( m_last_value); }


	void addWeightFunction(IFunction::ptr ptr)
	{
		m_weight_function = std::move(ptr);
	}

	std::string const& getName() const { return m_name; }
	void setName(std::string name) { m_name = name; }
};



using ConsiderationPtr = std::shared_ptr<IConsideration>;
