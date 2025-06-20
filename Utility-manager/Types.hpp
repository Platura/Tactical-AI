#pragma once
#include <stdint.h>



using aiInt =  int32_t;
using aiUInt = uint32_t;
using aiFloat = float;

struct Vec2D {
	aiFloat x;
	aiFloat y;
};

struct VecInt2D {
	aiInt x;
	aiInt y;
};

using aiPosition = Vec2D;
using aiTeamId = uint32_t;
using aiAgentId = uint32_t;

constexpr aiAgentId NoAgent = 0;
constexpr aiTeamId NoTeam = 0;
