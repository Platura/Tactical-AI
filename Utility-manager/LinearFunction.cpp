#include "LinearFunction.h"
#include <algorithm>

float LinearFunction::compute(float in)
{
    auto erg = (in - m_min) / (m_max - m_min);
    return std::min(1.f, std::max(0.f,erg));
}

IFunction::ptr LinearFunction::create(json const& parameter)
{
    auto instance = std::make_unique<LinearFunction>();

    if(parameter.contains("min"))
        instance->m_min = parameter["min"];
    if (parameter.contains("max"))
        instance->m_max = parameter["max"];
    return std::move(instance);
}
