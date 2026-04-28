#pragma once

#include "Position.hpp"

#include <memory>
#include <string>
#include <unordered_map>

namespace sw::core
{
	class IActionNode;

	struct Unit
	{
		uint32_t unitId{};
		std::string unitType{};
		Position pos{};
		std::unordered_map<std::string, uint32_t> stats{};
		std::shared_ptr<IActionNode> behaviour{};
	};
}
