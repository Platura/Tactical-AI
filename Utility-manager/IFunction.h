#pragma once
#include <memory>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class IFunction
{
public:
	using ptr = std::unique_ptr<IFunction>;

	virtual ~IFunction() {};
	virtual float compute(float in) = 0;
};

