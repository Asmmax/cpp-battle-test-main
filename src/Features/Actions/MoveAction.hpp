#pragma once

#include <Core/Actions/IActionNode.hpp>

#include <cstdint>

namespace sw::features
{
	class MoveAction : public core::IActionNode
	{
	public:
		virtual bool execute(core::Unit& self, core::World& world) override;
	};
}
