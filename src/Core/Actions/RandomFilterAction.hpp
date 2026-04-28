#pragma once

#include "AContextActionNode.hpp"

#include <memory>
#include <vector>

namespace sw::core
{
	class RandomFilterAction : public AContextActionNode<std::vector<uint32_t>>
	{
	public:
		virtual bool execute(Unit& self, World& world, std::vector<uint32_t>& ctx) override;
	};
}
