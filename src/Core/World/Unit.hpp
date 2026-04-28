#pragma once

#include "Position.hpp"

#include <string>
#include <unordered_map>
#include <memory>

namespace sw::core
{
	class IAction;

	struct Unit
	{
		uint32_t unitId{};
		std::string unitType{};
		Position pos{};
		std::unordered_map<std::string, uint32_t> stats;
		std::shared_ptr<IAction> action;
	};
}
