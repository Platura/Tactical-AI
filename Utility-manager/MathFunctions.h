#pragma once
#include <math.h>


inline float getPartialLinear(float input, float min, float max)
{
	return ((input - min) / (max - min));
}


inline float getLinear(float input, float m)
{
	return (input / m);
}

inline float getQuadratic(float input, float m, float k)
{
	//strong change at the ends
	//if k between 0 and 1 the curve is rotated
	return std::pow(input / m, k);
}

inline float getLogistic(float input, float e=2.71)
{
	//strong change in the middle
	return (1 / std::pow(1 + e, -input));
}