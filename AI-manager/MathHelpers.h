#pragma once
#include <math.h>
template<typename VEC>
inline auto getLength(VEC const& a)
{
	return std::sqrt(a.x * a.x + a.y * a.y);
}

template<typename VEC>
inline auto getDistance(VEC const& a, VEC const& b)
{
	return getLength(a - b);
}

template<typename VEC>
inline auto getDirection(VEC const& a, VEC const& b)
{
	return ((b - a)/getLength(a-b));
}