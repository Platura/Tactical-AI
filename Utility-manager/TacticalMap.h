#pragma once
#include "Field.h"
#include "Types.hpp"

class TacticalMap : public Field<float>
{
private:

public:
	TacticalMap() = default;
	TacticalMap(uint32_t size_x, uint32_t size_y, float value = 0.f);
	TacticalMap(Field<float>&& value);
	TacticalMap(Field<float>& value);

	TacticalMap& operator*=(TacticalMap const& other);
	TacticalMap& operator*=(float const& value);
	TacticalMap& operator^=(TacticalMap const& other);
	TacticalMap& operator+=(TacticalMap const& other);
	TacticalMap& operator+=(float const& value);
	TacticalMap& operator/=(TacticalMap const& other);
	TacticalMap& operator/=(float const& value);
	TacticalMap& operator-=(TacticalMap const& other);

	//returns the map with weighted values
	TacticalMap& weight(float const& value);
	//returns the map with inverted values
	TacticalMap& invert();
	//returns the map with the max values
	TacticalMap& max(TacticalMap const& other);

	friend TacticalMap operator*(TacticalMap const& a, TacticalMap const& b);
	friend TacticalMap operator-(TacticalMap const& a, TacticalMap const& b);
	friend TacticalMap operator/(TacticalMap const& a, TacticalMap const& b);
	friend TacticalMap max(TacticalMap const& a, TacticalMap const& b);
	//returns new map with inverted values
	friend TacticalMap invert(TacticalMap const& a);

	aiPosition getMaxValue();

	std::vector<aiPosition> getTopNValues(int count);

};
 
