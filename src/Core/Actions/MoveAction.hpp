#pragma once

#include "IActionNode.hpp"

#include <cstdint>

namespace sw::core
{
	class MoveAction : public IActionNode
	{
	private:
		uint32_t _speed{};

	public:
		MoveAction(uint32_t speed = 1);

		virtual bool execute(Unit& self, World& world) override;
		virtual bool check(Unit& self, World& world) const override;
	};
}
