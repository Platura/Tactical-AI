#pragma once
#include "IFunction.h"
class IdentityFunction :
	public IFunction
{
public:
	float compute(float in)override;

	static IFunction::ptr create(json const& parameter);
};

