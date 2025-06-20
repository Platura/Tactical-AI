#include "IdentityFunction.h"

float IdentityFunction::compute(float in)
{
	return in;
}

IFunction::ptr IdentityFunction::create(json const& parameter)
{
	return std::make_unique<IdentityFunction>();
}
