#pragma once
#include "IFunction.h"
class LinearFunction :
    public IFunction
{
    float m_min = 0;
    float m_max = 1;
public:
    float compute(float in) override;

    static IFunction::ptr create(json const& parameter);

private:

};

