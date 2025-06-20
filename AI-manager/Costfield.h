#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include"Field.h"
#include "Grid.h"
class Costfield
{
public:
	Costfield() = default;
	Costfield(Field<int> const& tilemap);
	Costfield(Field<float> const& tilemap);


	void init(Field<int> const& tilemap);
	void init(Field<float> const& tilemap);

	Field<uint32_t> const& getData() const {
		return m_costField;
	}

	template<typename T>
	Field<T> convert(std::function<T(uint32_t value)> converter)
	{
		Field<T> result;
		result.init(m_costField.getSizeX(), m_costField.getSizeY(), T{});

		for (size_t i = 0; i < result.getSize(); ++i)
		{
			result.getData()[i] = converter(m_costField.getData()[i]);
		}
		return result;
	}
private:
	Field<uint32_t> m_costField;
	int m_costmod = 1;
};

