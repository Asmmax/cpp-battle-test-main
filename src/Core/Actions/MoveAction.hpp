#pragma once

#include "IActionNode.hpp"

#include <cstdint>

namespace sw::core
{
	class MoveAction : public IActionNode
	{
	public:
		virtual bool execute(Unit& self, World& world) override;
	};
}
